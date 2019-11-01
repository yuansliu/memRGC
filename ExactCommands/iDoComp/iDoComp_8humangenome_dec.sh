sh gendecodefile.sh HG17 HG18
sh gendecodefile.sh HG17 HG19
sh gendecodefile.sh HG17 HG38
sh gendecodefile.sh HG17 YH
sh gendecodefile.sh HG17 KO131
sh gendecodefile.sh HG17 KO224
sh gendecodefile.sh HG17 HuRef
sh gendecodefile.sh HG18 HG17
sh gendecodefile.sh HG18 HG19
sh gendecodefile.sh HG18 HG38
sh gendecodefile.sh HG18 YH
sh gendecodefile.sh HG18 KO131
sh gendecodefile.sh HG18 KO224
sh gendecodefile.sh HG18 HuRef
sh gendecodefile.sh HG19 HG17
sh gendecodefile.sh HG19 HG18
sh gendecodefile.sh HG19 HG38
sh gendecodefile.sh HG19 YH
sh gendecodefile.sh HG19 KO131
sh gendecodefile.sh HG19 KO224
sh gendecodefile.sh HG19 HuRef
sh gendecodefile.sh HG38 HG17
sh gendecodefile.sh HG38 HG18
sh gendecodefile.sh HG38 HG19
sh gendecodefile.sh HG38 YH
sh gendecodefile.sh HG38 KO131
sh gendecodefile.sh HG38 KO224
sh gendecodefile.sh HG38 HuRef
sh gendecodefile.sh YH HG17
sh gendecodefile.sh YH HG18
sh gendecodefile.sh YH HG19
sh gendecodefile.sh YH HG38
sh gendecodefile.sh YH KO131
sh gendecodefile.sh YH KO224
sh gendecodefile.sh YH HuRef
sh gendecodefile.sh KO131 HG17
sh gendecodefile.sh KO131 HG18
sh gendecodefile.sh KO131 HG19
sh gendecodefile.sh KO131 HG38
sh gendecodefile.sh KO131 YH
sh gendecodefile.sh KO131 KO224
sh gendecodefile.sh KO131 HuRef
sh gendecodefile.sh KO224 HG17
sh gendecodefile.sh KO224 HG18
sh gendecodefile.sh KO224 HG19
sh gendecodefile.sh KO224 HG38
sh gendecodefile.sh KO224 YH
sh gendecodefile.sh KO224 KO131
sh gendecodefile.sh KO224 HuRef
sh gendecodefile.sh HuRef HG17
sh gendecodefile.sh HuRef HG18
sh gendecodefile.sh HuRef HG19
sh gendecodefile.sh HuRef HG38
sh gendecodefile.sh HuRef YH
sh gendecodefile.sh HuRef KO131
sh gendecodefile.sh HuRef KO224

nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_YH_decode.txt HG17_ref_YH/HG17_ref_YH' </dev/null 1> HG17_ref_YH_dec.out 2> HG17_ref_YH_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_YH_decode.txt HG18_ref_YH/HG18_ref_YH' </dev/null 1> HG18_ref_YH_dec.out 2> HG18_ref_YH_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_YH_decode.txt HG19_ref_YH/HG19_ref_YH' </dev/null 1> HG19_ref_YH_dec.out 2> HG19_ref_YH_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_YH_decode.txt HG38_ref_YH/HG38_ref_YH' </dev/null 1> HG38_ref_YH_dec.out 2> HG38_ref_YH_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_YH_decode.txt KO131_ref_YH/KO131_ref_YH' </dev/null 1> KO131_ref_YH_dec.out 2> KO131_ref_YH_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_YH_decode.txt KO224_ref_YH/KO224_ref_YH' </dev/null 1> KO224_ref_YH_dec.out 2> KO224_ref_YH_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_YH_decode.txt HuRef_ref_YH/HuRef_ref_YH' </dev/null 1> HuRef_ref_YH_dec.out 2> HuRef_ref_YH_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_HG17_decode.txt YH_ref_HG17/YH_ref_HG17' </dev/null 1> YH_ref_HG17_dec.out 2> YH_ref_HG17_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_HG17_decode.txt HG18_ref_HG17/HG18_ref_HG17' </dev/null 1> HG18_ref_HG17_dec.out 2> HG18_ref_HG17_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_HG17_decode.txt HG19_ref_HG17/HG19_ref_HG17' </dev/null 1> HG19_ref_HG17_dec.out 2> HG19_ref_HG17_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_HG17_decode.txt HG38_ref_HG17/HG38_ref_HG17' </dev/null 1> HG38_ref_HG17_dec.out 2> HG38_ref_HG17_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_HG17_decode.txt KO131_ref_HG17/KO131_ref_HG17' </dev/null 1> KO131_ref_HG17_dec.out 2> KO131_ref_HG17_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_HG17_decode.txt KO224_ref_HG17/KO224_ref_HG17' </dev/null 1> KO224_ref_HG17_dec.out 2> KO224_ref_HG17_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_HG17_decode.txt HuRef_ref_HG17/HuRef_ref_HG17' </dev/null 1> HuRef_ref_HG17_dec.out 2> HuRef_ref_HG17_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_HG18_decode.txt YH_ref_HG18/YH_ref_HG18' </dev/null 1> YH_ref_HG18_dec.out 2> YH_ref_HG18_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_HG18_decode.txt HG17_ref_HG18/HG17_ref_HG18' </dev/null 1> HG17_ref_HG18_dec.out 2> HG17_ref_HG18_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_HG18_decode.txt HG19_ref_HG18/HG19_ref_HG18' </dev/null 1> HG19_ref_HG18_dec.out 2> HG19_ref_HG18_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_HG18_decode.txt HG38_ref_HG18/HG38_ref_HG18' </dev/null 1> HG38_ref_HG18_dec.out 2> HG38_ref_HG18_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_HG18_decode.txt KO131_ref_HG18/KO131_ref_HG18' </dev/null 1> KO131_ref_HG18_dec.out 2> KO131_ref_HG18_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_HG18_decode.txt KO224_ref_HG18/KO224_ref_HG18' </dev/null 1> KO224_ref_HG18_dec.out 2> KO224_ref_HG18_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_HG18_decode.txt HuRef_ref_HG18/HuRef_ref_HG18' </dev/null 1> HuRef_ref_HG18_dec.out 2> HuRef_ref_HG18_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_HG19_decode.txt YH_ref_HG19/YH_ref_HG19' </dev/null 1> YH_ref_HG19_dec.out 2> YH_ref_HG19_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_HG19_decode.txt HG17_ref_HG19/HG17_ref_HG19' </dev/null 1> HG17_ref_HG19_dec.out 2> HG17_ref_HG19_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_HG19_decode.txt HG18_ref_HG19/HG18_ref_HG19' </dev/null 1> HG18_ref_HG19_dec.out 2> HG18_ref_HG19_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_HG19_decode.txt HG38_ref_HG19/HG38_ref_HG19' </dev/null 1> HG38_ref_HG19_dec.out 2> HG38_ref_HG19_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_HG19_decode.txt KO131_ref_HG19/KO131_ref_HG19' </dev/null 1> KO131_ref_HG19_dec.out 2> KO131_ref_HG19_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_HG19_decode.txt KO224_ref_HG19/KO224_ref_HG19' </dev/null 1> KO224_ref_HG19_dec.out 2> KO224_ref_HG19_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_HG19_decode.txt HuRef_ref_HG19/HuRef_ref_HG19' </dev/null 1> HuRef_ref_HG19_dec.out 2> HuRef_ref_HG19_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_HG38_decode.txt YH_ref_HG38/YH_ref_HG38' </dev/null 1> YH_ref_HG38_dec.out 2> YH_ref_HG38_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_HG38_decode.txt HG17_ref_HG38/HG17_ref_HG38' </dev/null 1> HG17_ref_HG38_dec.out 2> HG17_ref_HG38_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_HG38_decode.txt HG18_ref_HG38/HG18_ref_HG38' </dev/null 1> HG18_ref_HG38_dec.out 2> HG18_ref_HG38_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_HG38_decode.txt HG19_ref_HG38/HG19_ref_HG38' </dev/null 1> HG19_ref_HG38_dec.out 2> HG19_ref_HG38_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_HG38_decode.txt KO131_ref_HG38/KO131_ref_HG38' </dev/null 1> KO131_ref_HG38_dec.out 2> KO131_ref_HG38_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_HG38_decode.txt KO224_ref_HG38/KO224_ref_HG38' </dev/null 1> KO224_ref_HG38_dec.out 2> KO224_ref_HG38_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_HG38_decode.txt HuRef_ref_HG38/HuRef_ref_HG38' </dev/null 1> HuRef_ref_HG38_dec.out 2> HuRef_ref_HG38_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_KO131_decode.txt YH_ref_KO131/YH_ref_KO131' </dev/null 1> YH_ref_KO131_dec.out 2> YH_ref_KO131_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_KO131_decode.txt HG17_ref_KO131/HG17_ref_KO131' </dev/null 1> HG17_ref_KO131_dec.out 2> HG17_ref_KO131_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_KO131_decode.txt HG18_ref_KO131/HG18_ref_KO131' </dev/null 1> HG18_ref_KO131_dec.out 2> HG18_ref_KO131_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_KO131_decode.txt HG19_ref_KO131/HG19_ref_KO131' </dev/null 1> HG19_ref_KO131_dec.out 2> HG19_ref_KO131_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_KO131_decode.txt HG38_ref_KO131/HG38_ref_KO131' </dev/null 1> HG38_ref_KO131_dec.out 2> HG38_ref_KO131_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_KO131_decode.txt KO224_ref_KO131/KO224_ref_KO131' </dev/null 1> KO224_ref_KO131_dec.out 2> KO224_ref_KO131_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_KO131_decode.txt HuRef_ref_KO131/HuRef_ref_KO131' </dev/null 1> HuRef_ref_KO131_dec.out 2> HuRef_ref_KO131_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_KO224_decode.txt YH_ref_KO224/YH_ref_KO224' </dev/null 1> YH_ref_KO224_dec.out 2> YH_ref_KO224_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_KO224_decode.txt HG17_ref_KO224/HG17_ref_KO224' </dev/null 1> HG17_ref_KO224_dec.out 2> HG17_ref_KO224_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_KO224_decode.txt HG18_ref_KO224/HG18_ref_KO224' </dev/null 1> HG18_ref_KO224_dec.out 2> HG18_ref_KO224_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_KO224_decode.txt HG19_ref_KO224/HG19_ref_KO224' </dev/null 1> HG19_ref_KO224_dec.out 2> HG19_ref_KO224_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_KO224_decode.txt HG38_ref_KO224/HG38_ref_KO224' </dev/null 1> HG38_ref_KO224_dec.out 2> HG38_ref_KO224_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_KO224_decode.txt KO131_ref_KO224/KO131_ref_KO224' </dev/null 1> KO131_ref_KO224_dec.out 2> KO131_ref_KO224_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HuRef_ref_KO224_decode.txt HuRef_ref_KO224/HuRef_ref_KO224' </dev/null 1> HuRef_ref_KO224_dec.out 2> HuRef_ref_KO224_dec.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run d YH_ref_HuRef_decode.txt YH_ref_HuRef/YH_ref_HuRef' </dev/null 1> YH_ref_HuRef_dec.out 2> YH_ref_HuRef_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG17_ref_HuRef_decode.txt HG17_ref_HuRef/HG17_ref_HuRef' </dev/null 1> HG17_ref_HuRef_dec.out 2> HG17_ref_HuRef_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG18_ref_HuRef_decode.txt HG18_ref_HuRef/HG18_ref_HuRef' </dev/null 1> HG18_ref_HuRef_dec.out 2> HG18_ref_HuRef_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG19_ref_HuRef_decode.txt HG19_ref_HuRef/HG19_ref_HuRef' </dev/null 1> HG19_ref_HuRef_dec.out 2> HG19_ref_HuRef_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d HG38_ref_HuRef_decode.txt HG38_ref_HuRef/HG38_ref_HuRef' </dev/null 1> HG38_ref_HuRef_dec.out 2> HG38_ref_HuRef_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO131_ref_HuRef_decode.txt KO131_ref_HuRef/KO131_ref_HuRef' </dev/null 1> KO131_ref_HuRef_dec.out 2> KO131_ref_HuRef_dec.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run d KO224_ref_HuRef_decode.txt KO224_ref_HuRef/KO224_ref_HuRef' </dev/null 1> KO224_ref_HuRef_dec.out 2> KO224_ref_HuRef_dec.err
