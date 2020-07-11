from selenium.common.exceptions import TimeoutException, NoSuchElementException, ElementNotInteractableException
from selenium.webdriver.support.ui import Select
from time import sleep, time
from threading import Lock

import slaves.bakeca_constants as CONSTANTS
import util
import bot_logger
import traceback
import random
import queue
import os
import datetime
from proxy_tools import Proxy

# CONSTANTS
SCRIPT_DIR = os.path.dirname(os.path.realpath(__name__))
# NOTE: This should be moved in util. I think.
CREDENTIALS_DIR = os.path.join(SCRIPT_DIR, "credentials") + os.sep
BAKECA_CREDENTIALS_FILE = "bakeca_credentials.txt"
BAKECA_CREDENTIALS_PATH = os.path.join(CREDENTIALS_DIR, BAKECA_CREDENTIALS_FILE)
# File that contains the previous state
BAKECA_STATE_FILE = "bakeca_state.txt"
BAKECA_STATE_FILE_DIR = os.path.join(SCRIPT_DIR, "saved_states") + os.sep
BAKECA_STATE_FILE_PATH = os.path.join(BAKECA_STATE_FILE_DIR, BAKECA_STATE_FILE)
# TODO: redundant file definition (see default.cfg)
PROXY_INPUT_PATH = os.path.join(SCRIPT_DIR, "proxy_input.txt")
PROXY_OUTPUT_OK_PATH = os.path.join(SCRIPT_DIR, "proxy_output_ok.txt")
PROXY_OUTPUT_NOK_PATH = os.path.join(SCRIPT_DIR, "proxy_output_nok.txt")


BAKECA_SUCCESS = 1
BAKECA_ERROR = 0
BAKECA_RETRY = -1

class BakecaException(Exception):
	"""Raised for different internal errors"""
	pass

class CaptchaSolverException(Exception):
	"""Raised for different internal errors"""
	pass

class TelegramAuthException(Exception):
	"""Raised for different internal errors"""
	pass

class ProxyException(Exception):
	"""Raised for different proxy errors"""
	pass

################################################################################
################################################################################
########################### Bakeca Stuff ####################################
################################################################################
################################################################################
class BakecaSlave(object):
	""" Class that describes how a dincontri.com slave should behave """
	# Class specific variables
	# NOTE: Access to those variable should be atomic. We use 'bakeca_lock'
	# The queue is an asynchronous queue so it has that covered
	bakeca_lock = Lock()
	city_index = 0
	category_index = 0
	slave_index = 0
	text_file = None
	image_dir = None
	is_headless = True
	use_proxy = False
	use_lpm = False
	lpm_address = ""
	fail_queue = queue.Queue()

	def __init__(self, is_headless, use_proxy, use_lpm, lpm_address, disable_logging):
		with BakecaSlave.bakeca_lock:
			self.slave_id = util.random_string(8) + "-" + str(BakecaSlave.slave_index)
			BakecaSlave.slave_index = BakecaSlave.slave_index + 1
			if use_proxy:
				BakecaSlave.proxy = Proxy(PROXY_INPUT_PATH, PROXY_OUTPUT_OK_PATH, PROXY_OUTPUT_NOK_PATH)
				BakecaSlave.proxy.__enter__()

		self.logger = bot_logger.get_logger(
			name=__name__ + '-' + self.slave_id,
			log_file=__name__ + '-' + self.slave_id
		)
		self.disable_logging = disable_logging
		BakecaSlave.is_headless = is_headless
		BakecaSlave.use_proxy = use_proxy
		BakecaSlave.use_lpm = use_lpm
		BakecaSlave.lpm_address = lpm_address

	def parse_context(self, context):
		# This looks like it was written by a retard @retard_chief(you know who you are)
		# Although the fail case may never happen, it's still retarded
		if not BakecaSlave.image_dir and not BakecaSlave.text_file:
			with BakecaSlave.bakeca_lock:
				BakecaSlave.image_dir = context['image_dir']
				BakecaSlave.text_file = context['text_file']

	def register_to_website(self, driver, email, password):
		# Click on i'm over 18
		driver.find_element_by_xpath('//*[@id="content"]/a[1]').click()
		# Account button
		driver.find_element_by_xpath('/html/body/div/div[2]/table/tbody/tr/td[5]/a').click()
		# Register button
		driver.find_element_by_xpath('/html/body/div/div[2]/div[2]/div[2]/a[1]').click()

		# Fill in fields
		driver.find_element_by_xpath('//*[@id="UserEmail"]').send_keys(email)
		sleep(2)
		driver.find_element_by_xpath('//*[@id="UserPassword"]').send_keys(password)
		sleep(2)
		driver.find_element_by_xpath('//*[@id="UserPassword2"]').send_keys(password)

		# Solve captcha
		resp = util.solve_captcha(driver)
		if resp == "error":
			raise CaptchaSolverException("Failed to resolve captcha")
		# Close captcha response
		recaptcha_response = driver.find_element_by_id("g-recaptcha-response")
		driver.execute_script("arguments[0].style.display = 'none';", recaptcha_response)

		# Click on register
		util.scroll_into_view_click(driver, '/html/body/div[1]/div[2]/div[2]/div[2]/form/div[3]/input')
		return 0

	def login_to_website(self, driver, email, password):
		# Click on create announcement
		driver.find_element_by_xpath('/html/body/div[1]/div[2]/table/tbody/tr/td[3]/a').click()
		# Fill in credentials
		driver.find_element_by_xpath('//*[@id="UserEmail"]').send_keys(email)
		driver.find_element_by_xpath('//*[@id="UserPassword"]').send_keys(password)
		# Click on continue
		driver.find_element_by_xpath('/html/body/div/div[2]/div[3]/div[2]/form/div[2]/input').click()
		return 0

	def make_website_post(self, driver, city_id, category_id, title, content, images, email):
		# Get category and city
		city_name = CONSTANTS.CITIES[city_id]
		category_name = CONSTANTS.CATEGORIES[category_id]
		self.logger.info("Making website post for city [%s] and category [%s]..." % (city_name, category_name))
		# Click on create announcement
		# driver.find_element_by_xpath('//*[@id="button-base"]/a').click()
		driver.find_element_by_xpath('//*[ @ id = "navbarSupportedContent20"] / ul / li[3]').click()

		# Read the terms and conditions
		sleep(4)

		# Click on accept
		util.scroll_into_view_click(driver, '//*[@id="accetto"]')

		# Select city
		select = Select(driver.find_element_by_id('citta-ins'))
		select.select_by_visible_text(city_name)
		# Select cattegory
		select = Select(driver.find_element_by_id('categoria-ins'))
		select.select_by_visible_text(category_name)
		# Set title
		title_tag = driver.find_element_by_id('titolo-ins')
		driver.execute_script("arguments[0].scrollIntoView();", title_tag)
		title_tag.send_keys(title)
		# Set content
		content_tag = driver.find_element_by_id('testo-ins')
		driver.execute_script("arguments[0].scrollIntoView();", content_tag)
		content_tag.send_keys(content)

		# Photos
		# This tag is hidden
		file_tag_list = driver.find_element_by_id("upfile")
		driver.execute_script("arguments[0].style.display = 'block';", file_tag_list)
		driver.execute_script("arguments[0].scrollIntoView();", file_tag_list)

		# This tag is visible but is not input type=file
		# This means we do not load images in this tag
		# But we need to scroll into view maybe pop-up will not appear
		file_tag_visible = driver.find_element_by_xpath('//*[@id="image-upload-container-boxes"]/div[2]/div/div')
		driver.execute_script("arguments[0].scrollIntoView();", file_tag_visible)

		file_tag_list.send_keys(images[0] + " \n " + images[1] + " \n " + images[2] + " \n " + images[3] + " \n " + images[4])
		sleep(15)

		# # Add two more image fieds
		# # NOTE: If we change the number of images we should also change this
		# sleep(3)
		# driver.find_element_by_id('nuovaImagine').click()
		# driver.find_element_by_id('nuovaImagine').click()

		# # # Add images
		# driver.find_element_by_id('Gallery0Image').send_keys(images[0])
		# driver.find_element_by_id('Gallery1Image').send_keys(images[1])
		# driver.find_element_by_id('Gallery2Image').send_keys(images[2])
		# Wait for images

		# CHIUDI refers to 'something went wrong with the images'
		is_chiudi = False
		try:
			# Click on CHIUDI, whatever the fuck that means
			driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/div[2]/div/button').click()
			is_chiudi = True
		except NoSuchElementException as e:
			print("---> No CHIUDI message, and that's ok")
			self.logger.info("---> No CHIUDI message, and that's ok")

		# Get number of images loaded
		some_list = driver.find_elements_by_class_name('icon-rotate')
		# Minus 2 cuz there are 2 more element with that class located in the page
		loaded_images = len(some_list) - 2
		self.logger.info("---> Images loaded: " + str(loaded_images))


		# Email
		email_tag = driver.find_element_by_id('email-ins')
		driver.execute_script("arguments[0].scrollIntoView();", email_tag)
		email_tag.send_keys(email)

		# Solve captcha
		resp = util.solve_captcha_iframe(driver, '//*[@id="captcha_post_insert"]/div/div/iframe')
		if resp == "error":
			raise CaptchaSolverException("Failed to resolve captcha")
		# Close captcha response
		recaptcha_response = driver.find_element_by_id("g-recaptcha-response")
		driver.execute_script("arguments[0].style.display = 'none';", recaptcha_response)

		# Click on accept terms
		util.scroll_into_view_click(driver, '//*[@id="privacy-ins"]')

		# Accept cookies before submitting
		try:
			util.scroll_into_view_click(driver, '//*[@id="accept-gdpr"]')
		except NoSuchElementException as e:
			print("---> No cookies button!")

		# Click on accept terms
		util.scroll_into_view_click(driver, '//*[@id="submit-ins"]')

		# Click on promotion banner
		try:
			util.scroll_into_view_click(driver, '//*[@id="content-black-week-promo"]/div[2]/div[2]/div[6]/button')
		except NoSuchElementException as e:
			print("---> No promotion banner!")

		# Sleep for loading
		sleep(5)
		is_telegram_auth = False
		telegram_auth_block = driver.find_element_by_class_name("controllo-eta-container")
		display_attr = telegram_auth_block.get_attribute("display")

		if 'block' in str(display_attr) or 'Block' in str(display_attr):
			is_telegram_auth = True
			print('----> TELEGRAM AUTH')
			self.logger.info("----> TELEGRAM AUTH")
		else:
			print('----> NO telegram AUTH')
			self.logger.info("----> NO telegram AUTH")

		# Click on publish for free
		util.scroll_into_view_click(driver, '//*[@id="pub-gratis"]')

		return is_telegram_auth, is_chiudi, loaded_images


	def read_last_state(self):
		"""
		First try and read state from file. Possible cases:
			1. File does not exist. This is the first time the master bot started.
		We create the file and save out state in that file
			2. The file exists, and the this is the first iteration of the slave.
		We read the state from the file and continue executing from where we left.
			3. The file exists, but this is not the first iteration of the slave.
		We do not read the file, instead we continue with out normal execution
		NOTE: Don't know if we should make a util function from this. It seems
		all bots have city & category, but others may have additional data.
		"""
		city_id = None
		category_id = None
		# If 'city_index' and 'category_index' are not both 0, this means the slave
		# was previously executed so we don't care for the last state
		if BakecaSlave.city_index != 0 or BakecaSlave.category_index != 0:
			self.logger.info("Failed to read state from file...")
			return False

		# There is no state file. Return None.
		if not os.path.exists(BAKECA_STATE_FILE_PATH):
			self.logger.info("Failed to read state from file 2...")
			return False

		# Read last state from file
		with open(BAKECA_STATE_FILE_PATH, "r") as state_file:
			# City should be on first line
			# Category should be on second line
			lines = state_file.read().splitlines()
			# File is not as we expected it
			if len(lines) < 2:
				return city_id, category_id
			city_id = int(lines[0].split(":")[1])
			category_id = int(lines[1].split(":")[1])

		self.logger.info("Read state from file. City [%d] Category [%d]." % (city_id, category_id))
		BakecaSlave.city_index = city_id
		BakecaSlave.category_index = category_id
		return True

	def write_last_state(self):
		self.logger.info("Write state to file. City [%d] Category [%d]." % (BakecaSlave.city_index, BakecaSlave.category_index))
		with open(BAKECA_STATE_FILE_PATH, "w+") as state_file:
			state_file.write("City:%d\nCategory:%d" % (BakecaSlave.city_index, BakecaSlave.category_index))

	def get_additional_data(self):
		city_id = None
		category_id = None

		with BakecaSlave.bakeca_lock:
			# First try and get city and category from fail queue
			if not BakecaSlave.fail_queue.empty():
				city_id, category_id = BakecaSlave.fail_queue.get()
			# If queue is empty, get city and category as normal
			else:
				city_id = BakecaSlave.city_index
				category_id = BakecaSlave.category_index
				# Increment values for next thread to use
				if BakecaSlave.category_index == (len(CONSTANTS.CATEGORIES) - 1):
					BakecaSlave.city_index = (BakecaSlave.city_index + 1) % len(CONSTANTS.CITIES)
				BakecaSlave.category_index = (BakecaSlave.category_index + 1) % len(CONSTANTS.CATEGORIES)
		return city_id, category_id

	def push_to_fail_queue(self, city, category):
		# NOTE : The lock may not be needed
		with BakecaSlave.bakeca_lock:
			BakecaSlave.fail_queue.put((city, category))

################################################################################
################################################################################
########################## BAKECA Thread  ################################
################################################################################
################################################################################
	def start(self, context, return_queue):
		# Init script variables
		start = time()
		website_driver = None
		email_driver = None
		logger = self.logger
		disable_logging = self.disable_logging
		exception_raised = True
		exception_type = ""
		proxy_address = ""
		if BakecaSlave.use_proxy:
			proxy_address = BakecaSlave.proxy.get_address()
			if proxy_address is None:
				raise ProxyException("No more proxies available!")
		if BakecaSlave.use_lpm:
			proxy_address = BakecaSlave.lpm_address

		# Try and read last state from file
		self.read_last_state()
		# Get city and category and increment as needed
		city_id, category_id = self.get_additional_data()
		# Get image file and text file
		self.parse_context(context)
		logger.info("Parsed context %s." % str(context))

		try:
			# First go and get mail
			email_driver = util.get_chrome_driver(BakecaSlave.is_headless, proxy_address)
			util.go_to_page(driver=email_driver, page_url=util.MOAKT_URL)

			# Get text from file
			logger.info("Getting title and content...")
			title, content = util.parse_text_file(BakecaSlave.text_file)
			logger.info("Got title and content.")
			# Get email address
			email = util.moakt_get_email_address(email_driver)
			password = util.random_string(10)
			# Get images
			logger.info("Got email [%s] and password [%s]" % (email, password))
			images, out_message = util.get_images(BakecaSlave.image_dir)
			logger.info(out_message)

			# Go to Site
			logger.info("Opening website page...")
			website_driver = util.get_chrome_driver(BakecaSlave.is_headless, proxy_address)
			util.go_to_page(driver=website_driver, page_url=CONSTANTS.WEBSITE_URL)

			# Post without register
			logger.info("Make website post...")
			is_telg_auth, is_chiudi, loaded_images = self.make_website_post(website_driver, city_id, category_id, title, content, images, email)

			# Close website driver
			website_driver.quit()

			# If not TELEGRAM Auth continue with post flow
			if not is_telg_auth:
				# Sleep for mail to arrive
				sleep(5)
				# Go to mail box
				logger.info("Verify email...")
				util.moakt_access_verify_link(email_driver, '/html/body/p[5]/a')

				# Click on accept
				util.scroll_into_view_click(email_driver, '//*[@id="accetto"]')

				# Get post link
				logger.info("Getting post url...")
				announce_link = email_driver.find_element_by_xpath('//*[@id="colonna-unica"]/div[1]/p[1]/a')
				post_url = announce_link.get_attribute('href')

				# Close email driver
				email_driver.quit()

				print(post_url)
				end = time()
			exception_raised = False

		except TimeoutException as e:
			exception_type = "Timeout on page wait."
			logger.exception("Timeout on page wait.")
			raise BAKECAException("Timeout on page wait.")
		except NoSuchElementException as e:
			exception_type = "Element not found."
			logger.exception("Element not found.")
			raise BAKECAException("Element not found.")
		except ElementNotInteractableException as e:
			exception_type = "Element not interactable."
			logger.exception("Element not interactable.")
			raise BAKECAException("Element not interactable.")
		except util.UtilParseError as e:
			exception_type = "Parse error."
			logger.exception("Parse error.")
			raise BAKECAException("Parse error.")
		except CaptchaSolverException as e:
			exception_type = "Failed to solve captcha in time."
			logger.exception("Failed to solve captcha in time.")
			raise BAKECAException("Failed to solve captcha in time.")
		except TelegramAuthException as e:
			exception_type = "TelegramAuth was required."
			logger.exception("TelegramAuth was required.")
			raise BAKECAException("TelegramAuth was required.")
		except BakecaException as e:
			exception_type = "Bakeca exception occurred"
			logger.exception("Bakeca exception occurred")
		except Exception as e:
			exception_type = "Unknown error."
			logger.exception("Unknown error.")
			raise BAKECAException("Unknown error.")
		finally:
			# Close driver
			if email_driver is not None:
				email_driver.quit()
			if website_driver is not None:
				website_driver.quit()
			if BakecaSlave.use_proxy:
				BakecaSlave.proxy.set_valid(False)
				BakecaSlave.proxy.__exit__(None, None, None)
			self.write_last_state()
			if exception_raised:
				end = time()
				logger.info("Exception was raised. Writing error to credentials.")
				util.save_credentials_error(BAKECA_CREDENTIALS_PATH, exception_type, "bakeca.com", CONSTANTS.CITIES[city_id], CONSTANTS.CATEGORIES[category_id], end - start, BakecaSlave.bakeca_lock)
				logger.info("BAKECA !!!FAILED!!! For City %s and category %s." % (CONSTANTS.CITIES[city_id], CONSTANTS.CATEGORIES[category_id]))
				print("------> BAKECA !!!FAILED!!! For City %s and category %s. <------" % (CONSTANTS.CITIES[city_id], CONSTANTS.CATEGORIES[category_id]))
				self.push_to_fail_queue(city_id, category_id)
				bot_logger.close_logger(logger, disable_logging)

				# if failed to solve captcha simply retry
				if exception_type is "Failed to solve captcha in time.":
					return_queue.put(BAKECA_RETRY)
					return BAKECA_RETRY
				else:
					return_queue.put(BAKECA_ERROR)
					return BAKECA_ERROR

		# Success - save credentials and post url
		website = "bakeca.com" + "\n" + "City: " + CONSTANTS.CITIES[city_id] + "\n" + "Category: " + CONSTANTS.CATEGORIES[category_id] + "\n" + "Is chiudi: " + str(is_chiudi) + "\n" + "Images loaded: " + str(loaded_images)

		if is_telg_auth:
			util.save_credentials(BAKECA_CREDENTIALS_PATH, email, password, "FAILED - TELEGRAM AUTH REQUIRED",
				website, end - start, BakecaSlave.bakeca_lock)
		else:
			util.save_credentials(BAKECA_CREDENTIALS_PATH, email, password, post_url,
				website, end - start, BakecaSlave.bakeca_lock)

		announce_msg = ("BAKECA Success For City %s and category %s." % (CONSTANTS.CITIES[city_id], CONSTANTS.CATEGORIES[category_id]))
		print(announce_msg)
		logger.info(announce_msg)

		bot_logger.close_logger(logger, disable_logging)
		return_queue.put(BAKECA_SUCCESS)

		if BakecaSlave.use_proxy:
			BakecaSlave.proxy.set_valid(True)
			BakecaSlave.proxy.__exit__(None, None, None)

		return BAKECA_SUCCESS
