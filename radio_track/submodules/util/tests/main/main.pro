
QMAKE_CXXFLAGS += -std=c++17

TEMPLATE = app
TARGET = test_main
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += testcase
DESTDIR = $$PWD/../../bin
LIBS += -lboost_system -lboost_unit_test_framework -lpthread

INCLUDEPATH += \
    ./../../include

HEADERS += \
    ./../../include/utils/active.hpp \
    ./../../include/utils/blocks_pool.hpp \
    ./../../include/utils/connection.hpp \
    ./../../include/utils/boost_test_ex/check_close_collections.hpp \
    ./../../include/utils/disable_crash_dialog.hpp \
    ./../../include/utils/enum_traits.hpp \
    ./../../include/utils/event.hpp \
    ./../../include/utils/exception_catcher.hpp \
    ./../../include/utils/factory.hpp \
    ./../../include/utils/free_function_helper.hpp \
    ./../../include/utils/generate_has_member.hpp \
    ./../../include/utils/has_field.hpp \
    ./../../include/utils/integer_cast.hpp \
    ./../../include/utils/logger.hpp \
    ./../../include/utils/logging.hpp \
    ./../../include/utils/match.hpp \
    ./../../include/utils/multi_active.hpp \
    ./../../include/utils/overloaded.hpp \
    ./../../include/utils/parameters.hpp \
    ./../../include/utils/pimpl.hpp \
    ./../../include/utils/pointer_cast.hpp \
    ./../../include/utils/propagate_const.hpp \
    ./../../include/utils/propagate_const/propagate_const.hpp \
    ./../../include/utils/qstring_convert.hpp \
    ./../../include/utils/safe_invoke.hpp \
    ./../../include/utils/signals_wait.hpp \
    ./../../include/utils/string_utils.hpp \
    ./../../include/utils/thread_name.hpp \
    ./../../include/utils/threadsafe_limited_queue.hpp \
    ./../../include/utils/threadsafe_limited_stack.hpp \
    ./../../include/utils/threadsafe_list.hpp \
    ./../../include/utils/threadsafe_queue.hpp \
    ./../../include/utils/threadsafe_queue_batch.hpp

SOURCES += \
    main.cpp \
    test_active.cpp \
    test_blocks_pool.cpp \
    test_connection.cpp \
    test_enum_traits.cpp \
    test_event.cpp \
    test_exception_catcher.cpp \
    test_factory.cpp \
    test_free_function_helper.cpp \
    test_has_field.cpp \
    test_integer_cast.cpp \
    test_match.cpp \
    test_multi_active.cpp \
    test_safe_invoke.cpp \
    test_string_utils.cpp \
    test_threadsafe_limited_queue.cpp \
    test_threadsafe_limited_stack.cpp \
    test_threadsafe_list.cpp \
    test_threadsafe_queue.cpp
