#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3.3/library/xml.etree.elementtree.html
import xml.etree.ElementTree as ET


tree = ET.parse('country_data.xml')
root = tree.getroot()

for child in root:
    print(child.tag, child.attrib)

# Modifying an XML File
for rank in root.iter('rank'):
    new_rank = int(rank.text) + 1
    rank.text = str(new_rank)
    rank.set('updated', 'yes')

for country in root.findall('country'):
    rank = int(country.find('rank').text)
    if rank > 50:
        root.remove(country)

tree.write('output.xml')
