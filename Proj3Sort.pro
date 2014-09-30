TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    SortingCompetition.cpp

HEADERS += \
    SortingCompetition.h

OTHER_FILES += \
    testfiles/aliceinwonderland.txt \
    testfiles/allfiles.txt \
    testfiles/bible.txt \
    testfiles/huckfinn.txt \
    testfiles/modestproposal.txt \
    testfiles/shakespeare.txt \
    testfiles/siddhartha.txt \
    testfiles/warandpeace.txt \
    thingsToChange

