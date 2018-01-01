.
    Reading on the delegating constructors in the tutorial:
    http://www.learncpp.com/cpp-tutorial/8-6-overlapping-and-delegating-constructors/

    A constructor initialization list can delegate to another constructor.
    (Obs: in the initialization list, not in the constructor body!!!)

    Prior to C++11 calling a constructor explicitly from another constructor
    creates a temporary object, initializes the temporary object using the
    constructor, and then discards it, leaving your original object unchanged.

    class C {
    public:
        C(int vA)
        {
            /* initialize for vA */
        }

        C(int vA, int vB) : C(vA)  // delegate to the above constructor
        {
            /* initialize for vB */
        }
    };

    The dyamond problem remains an issue. This cannnot solve such ambiguity.

    If a constructor initalization list calls itself directly or indirectly
    the program is ill-formed; no diagnostic is required.
