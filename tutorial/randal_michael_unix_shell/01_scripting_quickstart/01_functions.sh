#!/bin/bash

function f
{
    echo "echo from function f"
}

g()
{
    echo "echo from function g"
}

f
g
