from PIL import Image
from random import random,randrange
import os
import shutil


def change_pixels(image_in, image_out, no_of_pix):
    """change no_of_pix pixels from image_in into image_out"""
    img_orig = Image.open(image_in)
    img_new = img_orig.copy()

    pixels_new = img_new.load()
    width = img_new.size[0]
    height = img_new.size[1]

    for i in range(0, no_of_pix):
        w = randrange(width-1)
        h = randrange(height-1)
        pix = pixels_new[w, h]
        r = max(0, pix[0] - 1)
        g = max(0, pix[1] - 1)
        b = max(0, pix[2] - 1)
        pixels_new[w, h] = (r, g, b)

    img_orig.close()
    img_new.save(image_out)
    img_new.close()


def change_pixels_in_place(image_in, no_of_pix):
    dir_name, basename = os.path.split(image_in)
    file_path, file_extension = os.path.splitext(image_in)
    image_out = os.path.join(dir_name, file_path + "_temp" + file_extension)
    change_pixels(image_in, image_out, no_of_pix)
    os.unlink(image_in)