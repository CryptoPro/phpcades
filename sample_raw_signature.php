<?php
try {
    $content = "Content to be signed";
    $subject = "test";
    $hd = new CPHashedData();
    $hd->set_Algorithm(CADESCOM_HASH_ALGORITHM_CP_GOST_3411_2012_256);
    $hd->Hash($content);

    $store = new CPStore();
    $store->Open(CURRENT_USER_STORE, "My", STORE_OPEN_READ_ONLY);
    $certs = $store->get_Certificates();
    $certs = $certs->Find(CERTIFICATE_FIND_SUBJECT_NAME, $subject, 0);
    $cert = $certs->Item(1);

    $rs = new CPRawSignature();
    $sig = $rs->SignHash($hd, $cert);
    printf("Signature: %s\n", $sig);

    $rsverify = new CPRawSignature();
    // CADES-2545: wrong parameter order
    $rsverify->VerifyHash($hd, $sig, $cert);
    $rsverify->VerifyHash($hd, $cert, $sig);
    printf("Verified successfully\n");
}
catch(Exception $e) {
    printf("Failed: %s\n", $e->getMessage());
}
?>
