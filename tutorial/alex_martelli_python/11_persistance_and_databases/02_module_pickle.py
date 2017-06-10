#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 279, The pickle and cPickle Modules
#           The pickle and cPickle modules supply factory functions, named
#           Pickler and Unpickler, to generate objects that wrap file-like
#           objects and supply serialization mechanisms. Serializing and
#           deserializing via these modules is also known as pickling and
#           unpickling. The difference between the modules is that, in pickle,
#           Pickler and Unpickler are classes, so you can inherit from these
#           classes to create customized serializer objects, overriding methods
#           as needed. In cPickle, on the other hand, Pickler and Unpickler are
#           factory functions that generate instances of non-subclassable types
#           not classes. Performance is much better with cPickle, but
#           inheritance is not feasible.
#           Note that unpickling from an untrusted data source is a security
#           risk; an attacker could exploit this to execute arbitrary code.
#           Don’t unpickle untrusted data!


import pickle
import os


#    https://wiki.python.org/moin/UsingPickle
#    Save a dictionary into a pickle file.
favorite_color = {"lion": "yellow", "kitty": "red"}
pickle.dump(favorite_color, open("save.p", "wb"))

#    Load the dictionary back from the pickle file.
pickle_color = pickle.load(open("save.p", "rb"))

print("serialized   color:", favorite_color)
print("deserialized color:", pickle_color)

#    Clean
os.unlink("save.p")
