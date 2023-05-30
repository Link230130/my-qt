QT += widgets
requires(qtConfig(tableview))

HEADERS     = delegate.h \
    form.h \
    widgetdelegate.h
SOURCES     = delegate.cpp \
              form.cpp \
              main.cpp \
              widgetdelegate.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/spinboxdelegate
INSTALLS += target

FORMS += \
    form.ui
