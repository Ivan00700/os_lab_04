all: static dynamic

# Компиляция библиотек
libimpl1.so: realization_1.c
	gcc -shared -fPIC realization_1.c -o libimpl1.so

libimpl2.so: realization_2.c
	gcc -shared -fPIC realization_2.c -o libimpl2.so

# Программа 1: Линкуется с libimpl1 на этапе компиляции
# -L. указывает искать либы в текущей папке
# -Wl,-rpath,. указывает запускаемому файлу искать .so в текущей папке
static: static.c libimpl1.so
	gcc static.c -L. -limpl1 -Wl,-rpath,. -o static

# Программа 2: Требует библиотеку dl для работы dlopen
dynamic: dynamic.c libimpl1.so libimpl2.so
	gcc dynamic.c -ldl -o dynamic

clean:
	rm -f *.so static dynamic