# отключаем создание ZERO проекта при сборке CMake
set(CMAKE_SUPPRESS_REGENERATION true)

# указывайте последнюю доступную вам версию CMake
cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

# название проекта
project(Laboratory_works)

# устанавливаем автоматическую инициализацию С++20
set(CMAKE_CXX_STANDARD 20)   

# подключение модуля FetchContent
include(FetchContent)

# скачивания архива гугл тестов
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# отключаем возможность изменять параметры компилятора/линковщика родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# гарантируем, что именованные зависимости были заполнены
FetchContent_MakeAvailable(googletest)

# затем следует список инструкций для подключения проектов из подкаталогов
include(LIBS/lib_cmake_funcs/function.cmake)    # подхватываем функции, реализованные в файле function.cmake

add_subdirectory(LIBS/lib_bitfield)     	# подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_bitfield
add_subdirectory(LIBS/lib_set)           	# подключаем дополнительный CMakeLists.txt из подкаталога с именем lib_set
add_subdirectory(LIBS/lib_Matrix)  
add_subdirectory(APPS/app_Application_Set)
add_subdirectory(TESTS/Tests_Set) 
add_subdirectory(APPS/app_Application_Matrix)
add_subdirectory(TESTS/Tests_Matrix)
add_subdirectory(LIBS/lib_Menu)
add_subdirectory(LIBS/lib_Stack)
add_subdirectory(TESTS/Tests_Stack)
add_subdirectory(APPS/app_Application_Stack)



