#Encoding utf-8

Для сборки расширения libphpcades вам потребуется libboost-dev, php-dev

1. Устанавливаем КриптоПро CSP + пакет devel + cprocsp-pki-cades
2. В файле /opt/cprocsp/src/phpcades/Makefile.unix в переменную PHPDIR прописываем путь к хедерам нужной версии php.
3. Для сборки расширения в папке /opt/cprocsp/src/phpcades выполняем 
   eval `/opt/cprocsp/src/samples/CSP/../setenv.sh --64`; make -f Makefile.unix или
   eval `/opt/cprocsp/src/samples/CSP/../setenv.sh --32`; make -f Makefile.unix
   в зависимости от битности системы.
4. В выводе php -i | grep extension_dir получаем путь к папке с расширениями и создаем там симплинк на 
   собранную libphpcades.so
5. В файле php.ini пишем extension=libphpcades.so
