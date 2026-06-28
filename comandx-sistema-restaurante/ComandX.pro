TEMPLATE = subdirs

SUBDIRS += \
    libs \
    app \
    tests

app.depends = libs
