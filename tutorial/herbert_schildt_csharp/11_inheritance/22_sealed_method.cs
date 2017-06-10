/*
    One other point: sealed can also be used on virtual methods to prevent
    further overrrides.
*/

class B
{
    public virtual void MyMethod() { /* ... */ }
}

class D : B
{
    // This seals MyMethod() and prevents further overrides.

    sealed public override void MyMethod() { /* ... */ }
}


class X : D
{
    // Error! MyMethod() is sealed!

    public override void MyMethod() { /* ... */ }
}
