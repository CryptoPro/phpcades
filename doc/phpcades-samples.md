Пример использования phpcades
===
Для работы примеров необходим сертификат с привязкой к закрытому ключу.

Тестовый сертификат можно установить с помощью команды (для amd64):
```bash
/opt/cprocsp/bin/amd64/cryptcp -createcert -dn "CN=test" -provtype 80 -cont '\\.\HDIMAGE\test' -ca https://cryptopro.ru/certsrv
```

В данном разделе
---

[Пример создания и проверки подписи](../samples/test_extension.php)<br>
[Пример создания и проверки подписи с помощью объекта RawSignature](../samples/sample_raw_signature.php)<br>