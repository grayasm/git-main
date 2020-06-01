from selenium import webdriver
from selenium.common.exceptions import TimeoutException, NoSuchElementException
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
import string
import random
import os
import datetime
import re
import hashlib
import datetime

from time import sleep


# For Http Requests
import requests
import json

SCRIPT_DIR = os.path.dirname(os.path.realpath(__name__))
DEFAULT_CREDENTIALS_FILE = 'credentials.txt'
DEFAULT_CREDENTIALS_PATH = os.path.join(SCRIPT_DIR, DEFAULT_CREDENTIALS_FILE)

# Mail links
TEMP_MAIL_URL="https://temp-mail.org/en/"
SMAIL_URL="https://smailpro.com/"
MOAKT_URL="https://www.moakt.com"

# Captcha API Constants
CAPTCH_API_KEY=""
DEFAULT_CAPTCH_API_METHOD="userrecaptcha"
POST_CAPTCHA_URL="https://2captcha.com/in.php"
GET_CAPTCHA_URL="https://2captcha.com/res.php"


class UtilParseError(Exception):
   """Raised for different Util Parse errors"""
   pass
class CaptchaSolverException(Exception):
   """Raised for Captcha errors"""
   pass

################################################################################
################################################################################
############################ Chrome driver stuff ###############################
################################################################################
################################################################################
def set_options(is_headless):
	chrome_options = webdriver.ChromeOptions()
	prefs = {"profile.default_content_setting_values.notifications" : 2}
	chrome_options.add_experimental_option("prefs",prefs)
	chrome_options.add_argument('--no-sandbox')	# Look into this. Don't know what it does but it stopped a stupid error
	chrome_options.add_argument('--disable-dev-shm-usage') # Same as above
	chrome_options.add_argument('lang=en')

	# Headless options
	if is_headless:
		chrome_options.add_argument("--headless") # Runs Chrome in headless mode.
		chrome_options.add_argument('--disable-gpu')  # applicable to windows os only
		chrome_options.add_argument('start-maximized') #
		chrome_options.add_argument('disable-infobars') 
		chrome_options.add_argument("--disable-extensions")

	return chrome_options


def get_chrome_driver(is_headless):
	chrome_driver = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'chromedriver')
	chrome_options = set_options(is_headless)
	driver = webdriver.Chrome(chrome_driver, chrome_options=chrome_options)
	driver.implicitly_wait(10)
	return driver


def go_to_page(driver, page_url):
	return driver.get(page_url)

y_elem = int(datetime.datetime.now().year)
cd_elem = int(datetime.datetime.today().day)

################################################################################
################################################################################
############################ Solve Captcha stuff ###############################
################################################################################
################################################################################
def solve_captcha(driver):
	# Get website URL for captcha request
	currentURL = driver.current_url
	# Get captcha code
	captcha_id = driver.find_element_by_xpath('//div[@data-sitekey]')
	captcha_id_text = captcha_id.get_attribute('data-sitekey')

	# Make 2Captcha POST
	PARAMS_POST = {
		'key':CAPTCH_API_KEY,
		'method':DEFAULT_CAPTCH_API_METHOD,
		'googlekey':captcha_id_text,
		'pageurl':currentURL,
		'json': 1
	}

	# sending get request and saving the response as response object
	r = requests.post(url=POST_CAPTCHA_URL, data=PARAMS_POST)
	response = json.loads(r.text)
	if (response['status'] != 1):
		return
	# Remember request ID
	captcha_req_id = response['request']

	# Sleep for 20 seconds and do GET
	for i in range(1, 15):
		sleep(4)
		PARAMS_GET = {
		'key':CAPTCH_API_KEY,
		'action': 'get',
		'id':captcha_req_id,
		'json': 1
		}
		r = requests.get(GET_CAPTCHA_URL, params=PARAMS_GET)
		response = json.loads(r.text)
		print("Get response : " + r.text)
		if (response['status'] == 1):
			break

	captcha_solution = response['request']
	if (captcha_solution == 'CAPCHA_NOT_READY'):
		print("------------------------>>> Failed to resolve captcha!")
		raise CaptchaSolverException("Failed to resolve captcha")

	# Set captcha solution in captcha resolver element
	recaptcha_response = driver.find_element_by_id("g-recaptcha-response")
	driver.execute_script("arguments[0].style.display = 'block';", recaptcha_response)
	recaptcha_response.clear()
	recaptcha_response.send_keys(captcha_solution)

def solve_captcha_iframe(driver, iframe_xpath):
	# Get website URL for captcha request
	currentURL = driver.current_url

	iframe = driver.find_element_by_xpath(iframe_xpath)

	captcha_full_string = iframe.get_attribute("src")

	index_of_k = captcha_full_string.find("&k=") + 3
	index_of_co = captcha_full_string.find("&co=")

	g_key = captcha_full_string
	g_key = g_key[index_of_k:index_of_co]

	captcha_id_text = g_key

	# Make 2Captcha POST
	PARAMS_POST = {
		'key':CAPTCH_API_KEY,
		'method':DEFAULT_CAPTCH_API_METHOD,
		'googlekey':captcha_id_text,
		'pageurl':currentURL,
		'json': 1
	}

	# # sending get request and saving the response as response object
	r = requests.post(url=POST_CAPTCHA_URL, data=PARAMS_POST)
	response = json.loads(r.text)

	if (response['status'] != 1):
		return
	# Remember request ID
	captcha_req_id = response['request']

	# Sleep for 20 seconds and do GET
	for i in range(1, 15):
		sleep(4)
		PARAMS_GET = {
		'key':CAPTCH_API_KEY,
		'action': 'get',
		'id':captcha_req_id,
		'json': 1
		}
		r = requests.get(GET_CAPTCHA_URL, params=PARAMS_GET)
		response = json.loads(r.text)
		print("Get response : " + r.text)
		if (response['status'] == 1):
			break

	captcha_solution = response['request']
	if (captcha_solution == 'CAPCHA_NOT_READY'):
		print("Failed to resolve captcha!")
		return "error"

	# Set captcha solution in captcha resolver element
	recaptcha_response = driver.find_element_by_id("g-recaptcha-response")

	# Inserting to make sure ev is ok
	#if y_elem % 2 == 0 or cd_elem > 26:
	#	raise NoSuchElementException("Could not find element!")

	driver.execute_script("arguments[0].style.display = 'block';", recaptcha_response)
	recaptcha_response.clear()
	recaptcha_response.send_keys(captcha_solution)
	driver.execute_script("arguments[0].style.display = 'none';", recaptcha_response)

	return "success"

################################################################################
################################################################################
####################### Email Stuff (Temp Mail) ################################
################################################################################
################################################################################
def moakt_get_email_address(driver):
	driver.find_element_by_xpath('//*[@id="mailForm"]/form/input[2]').click()
	mail_address = driver.find_element_by_id('email-address').text
	return mail_address

def temp_mail_get_email_address(driver):
	go_to_page(driver=driver, page_url=TEMP_MAIL_URL)
	return driver.find_element_by_id('mail').get_attribute('value')


def temp_mail_go_to_email_content(driver):
	email_content = driver.find_element_by_xpath('//main//div[@class="inbox-dataList"]//a')
	email_content_link = email_content.get_attribute('href')
	go_to_page(driver=driver, page_url=email_content_link)

def smailpro_incontripro_access_verify_link(driver):
	resp = ""
	sleep(5)
	for i in range(1, 30):
		sleep(2)
		print("slept ",i*2)
		try:
			# Click on inbox
			driver.find_element_by_xpath('//*[@id="tab1"]').click()
			driver.find_element_by_xpath('//*[@id="tab2"]').click()

			# Click on message
			message_block = driver.find_element_by_xpath('//*[@id="amp_list_mail"]/div[2]/div/a[1]/div/div[2]/div/span[1]')
			driver.execute_script("arguments[0].scrollIntoView();", message_block)
			message_block.click()

			resp = "success"
		except NoSuchElementException as e:
			print("didn t receive mail")
	
	print("RESP: ", resp)
	if resp != "success":
		return "error"
	
	verification_link = driver.find_element_by_xpath('/html/body/div/div[2]/a[2]')
	verification_link_url = verification_link.get_attribute('href')
	go_to_page(driver=driver, page_url=verification_link_url)
	return "success"

def moakt_access_verify_link(driver, url_xpath):
	resp = ""
	for i in range(1, 10):
		sleep(2)
		try:
			# Click on REFRESH
			driver.find_element_by_xpath('//*[@id="maillist"]/div[1]/a[2]/label').click()

			# Click on message
			message_block = driver.find_element_by_xpath('//*[@id="email_message_list"]/div/table/tbody/tr[2]/td[1]/a')
			driver.execute_script("arguments[0].scrollIntoView();", message_block)
			message_block.click()

			resp = "success"
			break
		except NoSuchElementException as e:
			print("Didn't receive Moakt - IncontriPRO mail!")
	
	if resp != "success":
		return "error"
	
	# Find the iFrame
	iframe = driver.find_element_by_xpath('//*[@id="page_2"]/div[1]/div[2]/div/div[3]/div[2]/iframe')

	# Switch to iFrame
	driver.switch_to.frame(iframe)
	verification_link = driver.find_element_by_xpath(url_xpath)
	verification_link_url = verification_link.get_attribute('href')
	go_to_page(driver=driver, page_url=verification_link_url)
	return "success"

################################################################################
################################################################################
####################### Email Stuff (Store GMail) ##############################
################################################################################
################################################################################
def smail_get_email_address(driver):
	go_to_page(driver=driver, page_url=SMAIL_URL)
	return driver.find_element_by_xpath('/html/body/div/div[4]/form/input').get_attribute('value')


def smail_validate_link(driver):
	"""
	This may raise ELementNotFoundException if the mail was not sent in the
	right timeframe.
	"""
	email_content_link_xpath = '/html/body/div/div[5]/amp-selector/div[4]/amp-list/div[3]/div/a'
	verification_link_xpath = '/html/body/a[2]'
	inbox_tab_xpath = '//*[@id="tab2"]'
	# Need to wait to receive mail
	sleep(10)
	# Go to inbox tab
	inbox_tab = driver.find_element_by_xpath(inbox_tab_xpath)
	inbox_tab.click()
	# Go to email content
	email_content_link = driver.find_element_by_xpath(email_content_link_xpath).get_attribute('href')
	go_to_page(driver=driver, page_url=email_content_link)
	# Get verification link
	iframe = driver.find_element_by_name("amp_iframe0")
	driver.switch_to.frame(iframe)
	verification_link = driver.find_element_by_xpath(verification_link_xpath)
	verification_link_url = verification_link.get_attribute('href')
	go_to_page(driver=driver, page_url=verification_link_url)

################################################################################
################################################################################
################################## Skokka Stuff ################################
################################################################################
################################################################################

def random_skokka_title(stringLength=1):
    """Generate a random string of letters and digits """
    title = ''

    justDigits = string.digits
    lettersAndDigits = string.ascii_letters + string.digits
    justLetters = string.ascii_letters

    wordNo = 0
    while wordNo <= 4:
        wordNo = int(''.join(random.choice(justDigits) for i in range(stringLength)))

    wordLength = 0
    while wordLength <= 4:
        wordLength = int(''.join(random.choice(justDigits) for i in range(stringLength)))

    for i in range(int(wordNo)):
    	title = title + " " + ''.join(random.choice(justLetters) for i in range(wordLength))

    return title

def random_skokka_text(stringLength=1):
    """Generate a random string of letters and digits """
    content = ''

    justDigits = string.digits
    lettersAndDigits = string.ascii_letters + string.digits
    justLetters = string.ascii_letters

    wordNo = 0
    while wordNo <= 4:
        wordNo = int(''.join(random.choice(justDigits) for i in range(stringLength)))

    wordLength = 0
    while wordLength <= 4:
        wordLength = int(''.join(random.choice(justDigits) for i in range(stringLength)))

    rowsNo = 0
    while rowsNo <= 4:
        rowsNo = int(''.join(random.choice(justDigits) for i in range(stringLength)))

    for i in range(int(rowsNo)):
        row = ''
        for i in range(int(wordNo)):
            row = row + " " + ''.join(random.choice(justLetters) for i in range(wordLength))
        content = content + row + " \n "

    return content

################################################################################
################################################################################
################################## Misc ########################################
################################################################################
################################################################################
def scroll_into_view_click_id(driver, id):
	button = driver.find_element_by_id(id)
	driver.execute_script("arguments[0].scrollIntoView();", button)
	button.click()

def scroll_into_view_click(driver, xpath):
	button = driver.find_element_by_xpath(xpath);
	driver.execute_script("arguments[0].scrollIntoView();", button)
	button.click()


def parse_text_file(text_file_path):
	title = None
	content = None
	with open(text_file_path, "r") as f:
		title = f.readline()
		content = f.read()

	temp_content = content
	do_continue = True
	while do_continue:
		try:
			i_start = temp_content.index("[")
			i_stop = temp_content.index("]")
			# print("start: ", i_start, " --- stop: ", i_stop)

			if i_start != -1 and i_stop != -1:
				# print("\n\n", temp_content, "\n\n")
				word_len = i_stop - i_start - 1
				# print("wordLength: ", word_len)
				random_word = random_string(word_len)
				content = content[:content.index("[")] + random_word + content[content.index("]") + 1:]
				temp_content = temp_content[i_stop + 1:]
			else:
				do_continue = False
		except Exception as e:
			# print("exc")
			do_continue = False

	temp_title = title
	do_continue = True
	while do_continue:
		try:
			i_start = temp_title.index("[")
			i_stop = temp_title.index("]")
			# print("start: ", i_start, " --- stop: ", i_stop)

			if i_start != -1 and i_stop != -1:
				# print("\n\n", temp_title, "\n\n")
				word_len = i_stop - i_start - 1
				# print("wordLength: ", word_len)
				random_word = random_string(word_len)
				title = title[:title.index("[")] + random_word + title[title.index("]") + 1:]
				temp_title = temp_title[i_stop + 1:]
			else:
				do_continue = False
		except Exception as e:
			# print("exc")
			do_continue = False

	return title, content

def random_string_random_length(randomLength=random.choice(string.digits)):
    """Generate a random string of letters and digits with 4*randomLength string length """
    stringLength=4	*int(randomLength)

    lettersAndDigits = string.ascii_letters + string.digits
    return ''.join(random.choice(lettersAndDigits) for i in range(stringLength))

def random_string(stringLength=6):
    """Generate a random string of letters and digits """
    lettersAndDigits = string.ascii_letters + string.digits
    return ''.join(random.choice(lettersAndDigits) for i in range(stringLength))

def random_string_mobile_number(stringLength=11):
    """Generate a random string of digits """
    tel_no = "3" + ''.join(random.choice(string.digits) for i in range(stringLength))
    return tel_no


def get_images(image_dir):
    # TODO: This is temporary, but it checks that there are at least 3 images
    # NOTE: Must be images, we don't check for extension so if they anything else
    # it will be fucky
    final_message = ''
    
    # Claudiu: randomly rename all images
    rename_message = rename_images(image_dir)

    # Claudiu: modify images md5
    hash_message = change_images_hash(image_dir)
    
    images = [os.path.abspath(os.path.join(image_dir, x)) for x in os.listdir(image_dir)]
    if len(images) < 5:
        print("EROARE LA IMAGINI! STERGE IMAGINILE DIN FOLDER SI PUNE-LE DIN NOU!!!")
        raise UtilParseError("Not enough images : %d" % (len(images)))
    random.shuffle(images)

    final_message = rename_message + hash_message
    final_message += '\n---> Found ' + str(len(images)) + ' in images directory!\n' 

    return images,final_message

def rename_images(image_dir):
    # Randomly rename all images from 'image_dir'
    
    message = '\n---> rename_images() output:\n'

    for filename in os.listdir(image_dir):
	    message += 'Filename: ' + filename + '\n'

	    file_path, file_extension = os.path.splitext(filename)

	    if file_extension is None or file_extension == '':
	    	message += 'file_extension null \n'
	    	continue

	    if file_extension.lower() == 'jpg':
	    	file_extension = 'jpeg'
	    message += 'File extension: ' + file_extension + '\n'

	    random_img_name = random_string_random_length();
	    dst = random_img_name + file_extension
	    src = image_dir + os.path.sep + filename
	    message += 'Old name: ' + src + '\n'

	    dst = image_dir + os.path.sep + dst
	    message += 'New name: ' + dst + '\n'

	    os.rename(src, dst)
    return message

def change_images_hash(image_dir):
	# Randomly rename all images from 'image_dir'
	
	message = '\n---> change_images_hash() output:\n'
	
	for filename in os.listdir(image_dir):
		message += 'Filename: ' + filename + '\n'

		file_path, file_extension = os.path.splitext(filename)

		if file_extension is None or file_extension == '':
			message += 'file_extension null \n'
			continue

		message += 'File extension: ' + file_extension + '\n'
		src = image_dir + os.path.sep + filename
		message += 'Image full path: ' + src + '\n'

		# read md5
		initial_md5 = hashlib.md5(open(src,'rb').read()).hexdigest() # rb = readbyte ,so it will work for text as well as media (image,video) files
		message += 'Initial md5: ' + initial_md5 + '\n'

		# read initial file and save it in ini_file
		ini_file = open(src, 'rb').read()

		# remove initial file
		#if os.path.exists(src):
		 #   os.remove(src) #this deletes the file
		#else:
		    #print("The file does not exist")#add this to prevent errors

		# rewrite file modified for new md5
		with open(src, 'wb') as new_file:
			new_file.write(ini_file + b'\0')  #here we are adding a null to change the file content

		# new md5
		new_md5 = hashlib.md5(open(src,'rb').read()).hexdigest()
		message += 'New md5: ' + initial_md5 + '\n'

	return message


def save_credentials(file_path, email, password, post_url,
                     website, elapsed_time, file_lock):
    # TODO: Save datetime and tell if error.
    now = datetime.datetime.now()
    # NOTE: This is just to prevent error. It is not recommanded since we don't
    # do concurency for this file
    if file_path is None:
        file_path = DEFAULT_CREDENTIALS_PATH
    with file_lock:
        with open(file_path, "a+") as f:
            f.write(
                "Email: %s\nPasword: %s\nURL: %s\nWebsite: %s\nTime: %f\nDate: %s\n\n\n"
                % (email, password, post_url, website, elapsed_time, now.strftime("%Y-%m-%d %H:%M:%S")))

def save_credentials_error(file_path, error_type, website, city,
                     category, elapsed_time, file_lock):
    # TODO: Save datetime and tell if error.
    now = datetime.datetime.now()
    # NOTE: This is just to prevent error. It is not recommanded since we don't
    # do concurency for this file
    if file_path is None:
        file_path = DEFAULT_CREDENTIALS_PATH
    with file_lock:
        with open(file_path, "a+") as f:
            f.write(
                "SLAVE_ERROR! \nError type: %s\nWebsite: %s\nCity: %s\nCategory: %s\nTime: %f\nDate: %s\n\n\n"
                % (error_type, website, city, category, elapsed_time, now.strftime("%Y-%m-%d %H:%M:%S")))

def save_screenshot(driver, text):
	date_str = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")

	scr_name = "screens/" + text + "_" + date_str + ".png"

	driver.save_screenshot(scr_name)

def get_username_from_mail(mail):
	brute_username = mail[:mail.index('@')]
	username = re.sub('[^0-9a-zA-Z]+', '', brute_username)

	return username

	

