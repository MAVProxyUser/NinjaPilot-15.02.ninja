# We use python3 to extract git version info and generate some other files.
# Python 2 is no longer supported.

# Try python3 first, then python if it's Python 3
PYTHON_VER = "$$system(python3 --version 2>&1)"
!isEmpty(PYTHON_VER):contains(PYTHON_VER, "Python 3.*") {
    PYTHON = \"python3\"
} else {
    PYTHON_VER = "$$system(python --version 2>&1)"
    contains(PYTHON_VER, "Python 3.*") {
        PYTHON = \"python\"
    } else {
        error(No Python 3 found. Please install python3.)
    }
}

PYTHON = $$replace(PYTHON, \\\\, /)
message(Using python interpreter: $$PYTHON)
