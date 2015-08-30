#!/usr/bin/env python3
"""pycsdl2 documentation build configuration file

This file is execfile()d with the current directory set to its containing dir.
"""


# -- General configuration ------------------------------------------------


source_suffix = '.rst'


master_doc = 'index'


project = 'pycsdl2'


copyright = '2015, Paul Tan'


# The short X.Y.Z version.
version = '2.0.0.0'


# The full version, including alpha/beta/rc tags.
release = '2.0.0.0.dev2'


language = 'en'


# -- Options for HTML output ----------------------------------------------


# Don't generate any module index because pycsdl2 consists of just one module
html_domain_indices = False


# Ensure that an index is generated
html_use_index = True


# The list of symbols is relatively small, so don't put each letter in a
# separate page.
html_split_index = False


# Output file base name for HTML help builder.
htmlhelp_basename = 'pycsdl2doc'


# -- Options for LaTeX output ---------------------------------------------


latex_elements = {
    # A4 is an ISO standard ;)
    'papersize': 'a4paper',

    # The font size
    'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    'preamble': '',
}


latex_documents = [
    (
        'index',  # source start file
        'pycsdl2.tex',  # target name
        'pycsdl2 Documentation',  # title
        'Paul Tan',  # author
        'manual',  # document class
    ),
]


# Ensure that an index is generated
latex_domain_indices = True


# -- Options for manual page output ---------------------------------------


man_pages = [
    (
        'index',  # source start file
        'pycsdl2',  # name
        'pycsdl2 Documentation',  # description
        ['Paul Tan'],  # authors
        1,  # manual section
    ),
]


# -- Options for Texinfo output -------------------------------------------


texinfo_documents = [
    (
        'index',  # source start file
        'pycsdl2',  # target name
        'pycsdl2 Documentation',  # title
        'Paul Tan',  # author
        'pycsdl2',  # dir menu entry
        'CPython binding for SDL2',  # description
        'Miscellaneous',  # category
    ),
]


# Ensure an index is generated
texinfo_domain_indices = True
