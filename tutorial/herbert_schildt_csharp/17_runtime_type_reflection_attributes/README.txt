.
    Runtime Type ID, Reflection, and Attributes

    This chapter discusses three interrelated and powerful features:
    (1) runtime type identification,
    (2) reflection, and
    (3) attributes.

    Runtime type ID is the mechanism that lets you identify a type during
    the execution of a program. Reflection is the feature that enables you
    to obtain information about a type. Using this information, you can
    construct and use objects at runtime. This feature is very powerful
    because it lets a program add functionality dynamically, during execution.
    An attribute describes a characteristic of some element of a C# program.
    For example, you can specify attributes for classes, methods, and fields,
    among others. Attributes can be interrogated at runtime, and the attribute
    information obtained. Attributes use both runtime type identification and
    reflection.


    Attributes

    C# allows you to add declarative information to a program in the form
    of an attribute. An attribute defines additional information (metadata)
    that is associated with a class, structure, method, and so on.
    For example, you might define an attribute that determines the type of
    button that a class will display. Attributes are specified between square
    brackets, preceding the item to which they apply. Thus, an attribute is
    not a member of a class. Rather, an attribute specifies supplemental
    information that is attached to an item.
