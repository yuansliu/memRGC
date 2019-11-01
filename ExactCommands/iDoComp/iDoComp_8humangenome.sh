mkdir HG17_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh HG17 HG17_sa' </dev/null 1> HG17_sa.out 2> HG17_sa.err
mkdir HG18_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh HG18 HG18_sa' </dev/null 1> HG18_sa.out 2> HG18_sa.err
mkdir HG19_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh HG19 HG19_sa' </dev/null 1> HG19_sa.out 2> HG19_sa.err
mkdir HG38_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh HG38 HG38_sa' </dev/null 1> HG38_sa.out 2> HG38_sa.err
mkdir YH_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh YH YH_sa' </dev/null 1> YH_sa.out 2> YH_sa.err
mkdir KO131_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh KO131 KO131_sa' </dev/null 1> KO131_sa.out 2> KO131_sa.err
mkdir KO224_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh KO224 KO224_sa' </dev/null 1> KO224_sa.out 2> KO224_sa.err
mkdir HuRef_sa
nohup bash -c '/usr/bin/time -v ./generateSA.sh HuRef HuRef_sa' </dev/null 1> HuRef_sa.out 2> HuRef_sa.err

sh genencodefile.sh HG17 HG18
sh genencodefile.sh HG17 HG19
sh genencodefile.sh HG17 HG38
sh genencodefile.sh HG17 YH
sh genencodefile.sh HG17 KO131
sh genencodefile.sh HG17 KO224
sh genencodefile.sh HG17 HuRef
sh genencodefile.sh HG18 HG17
sh genencodefile.sh HG18 HG19
sh genencodefile.sh HG18 HG38
sh genencodefile.sh HG18 YH
sh genencodefile.sh HG18 KO131
sh genencodefile.sh HG18 KO224
sh genencodefile.sh HG18 HuRef
sh genencodefile.sh HG19 HG17
sh genencodefile.sh HG19 HG18
sh genencodefile.sh HG19 HG38
sh genencodefile.sh HG19 YH
sh genencodefile.sh HG19 KO131
sh genencodefile.sh HG19 KO224
sh genencodefile.sh HG19 HuRef
sh genencodefile.sh HG38 HG17
sh genencodefile.sh HG38 HG18
sh genencodefile.sh HG38 HG19
sh genencodefile.sh HG38 YH
sh genencodefile.sh HG38 KO131
sh genencodefile.sh HG38 KO224
sh genencodefile.sh HG38 HuRef
sh genencodefile.sh YH HG17
sh genencodefile.sh YH HG18
sh genencodefile.sh YH HG19
sh genencodefile.sh YH HG38
sh genencodefile.sh YH KO131
sh genencodefile.sh YH KO224
sh genencodefile.sh YH HuRef
sh genencodefile.sh KO131 HG17
sh genencodefile.sh KO131 HG18
sh genencodefile.sh KO131 HG19
sh genencodefile.sh KO131 HG38
sh genencodefile.sh KO131 YH
sh genencodefile.sh KO131 KO224
sh genencodefile.sh KO131 HuRef
sh genencodefile.sh KO224 HG17
sh genencodefile.sh KO224 HG18
sh genencodefile.sh KO224 HG19
sh genencodefile.sh KO224 HG38
sh genencodefile.sh KO224 YH
sh genencodefile.sh KO224 KO131
sh genencodefile.sh KO224 HuRef
sh genencodefile.sh HuRef HG17
sh genencodefile.sh HuRef HG18
sh genencodefile.sh HuRef HG19
sh genencodefile.sh HuRef HG38
sh genencodefile.sh HuRef YH
sh genencodefile.sh HuRef KO131
sh genencodefile.sh HuRef KO224

nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_HG17_encode.txt YH_ref_HG17/YH_ref_HG17' </dev/null 1> YH_ref_HG17.out 2> YH_ref_HG17.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_HG17_encode.txt HG18_ref_HG17/HG18_ref_HG17' </dev/null 1> HG18_ref_HG17.out 2> HG18_ref_HG17.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_HG17_encode.txt HG19_ref_HG17/HG19_ref_HG17' </dev/null 1> HG19_ref_HG17.out 2> HG19_ref_HG17.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_HG17_encode.txt HG38_ref_HG17/HG38_ref_HG17' </dev/null 1> HG38_ref_HG17.out 2> HG38_ref_HG17.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_HG17_encode.txt KO131_ref_HG17/KO131_ref_HG17' </dev/null 1> KO131_ref_HG17.out 2> KO131_ref_HG17.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_HG17_encode.txt KO224_ref_HG17/KO224_ref_HG17' </dev/null 1> KO224_ref_HG17.out 2> KO224_ref_HG17.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_HG17_encode.txt HuRef_ref_HG17/HuRef_ref_HG17' </dev/null 1> HuRef_ref_HG17.out 2> HuRef_ref_HG17.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_HG18_encode.txt HG17_ref_HG18/HG17_ref_HG18' </dev/null 1> HG17_ref_HG18.out 2> HG17_ref_HG18.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_HG18_encode.txt HG19_ref_HG18/HG19_ref_HG18' </dev/null 1> HG19_ref_HG18.out 2> HG19_ref_HG18.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_HG18_encode.txt HG38_ref_HG18/HG38_ref_HG18' </dev/null 1> HG38_ref_HG18.out 2> HG38_ref_HG18.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_HG18_encode.txt YH_ref_HG18/YH_ref_HG18' </dev/null 1> YH_ref_HG18.out 2> YH_ref_HG18.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_HG18_encode.txt KO131_ref_HG18/KO131_ref_HG18' </dev/null 1> KO131_ref_HG18.out 2> KO131_ref_HG18.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_HG18_encode.txt KO224_ref_HG18/KO224_ref_HG18' </dev/null 1> KO224_ref_HG18.out 2> KO224_ref_HG18.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_HG18_encode.txt HuRef_ref_HG18/HuRef_ref_HG18' </dev/null 1> HuRef_ref_HG18.out 2> HuRef_ref_HG18.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_HG19_encode.txt HG17_ref_HG19/HG17_ref_HG19' </dev/null 1> HG17_ref_HG19.out 2> HG17_ref_HG19.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_HG19_encode.txt HG18_ref_HG19/HG18_ref_HG19' </dev/null 1> HG18_ref_HG19.out 2> HG18_ref_HG19.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_HG19_encode.txt HG38_ref_HG19/HG38_ref_HG19' </dev/null 1> HG38_ref_HG19.out 2> HG38_ref_HG19.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_HG19_encode.txt YH_ref_HG19/YH_ref_HG19' </dev/null 1> YH_ref_HG19.out 2> YH_ref_HG19.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_HG19_encode.txt KO131_ref_HG19/KO131_ref_HG19' </dev/null 1> KO131_ref_HG19.out 2> KO131_ref_HG19.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_HG19_encode.txt KO224_ref_HG19/KO224_ref_HG19' </dev/null 1> KO224_ref_HG19.out 2> KO224_ref_HG19.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_HG19_encode.txt HuRef_ref_HG19/HuRef_ref_HG19' </dev/null 1> HuRef_ref_HG19.out 2> HuRef_ref_HG19.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_HG38_encode.txt HG17_ref_HG38/HG17_ref_HG38' </dev/null 1> HG17_ref_HG38.out 2> HG17_ref_HG38.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_HG38_encode.txt HG18_ref_HG38/HG18_ref_HG38' </dev/null 1> HG18_ref_HG38.out 2> HG18_ref_HG38.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_HG38_encode.txt HG19_ref_HG38/HG19_ref_HG38' </dev/null 1> HG19_ref_HG38.out 2> HG19_ref_HG38.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_HG38_encode.txt YH_ref_HG38/YH_ref_HG38' </dev/null 1> YH_ref_HG38.out 2> YH_ref_HG38.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_HG38_encode.txt KO131_ref_HG38/KO131_ref_HG38' </dev/null 1> KO131_ref_HG38.out 2> KO131_ref_HG38.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_HG38_encode.txt KO224_ref_HG38/KO224_ref_HG38' </dev/null 1> KO224_ref_HG38.out 2> KO224_ref_HG38.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_HG38_encode.txt HuRef_ref_HG38/HuRef_ref_HG38' </dev/null 1> HuRef_ref_HG38.out 2> HuRef_ref_HG38.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_YH_encode.txt HG17_ref_YH/HG17_ref_YH' </dev/null 1> HG17_ref_YH.out 2> HG17_ref_YH.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_YH_encode.txt HG18_ref_YH/HG18_ref_YH' </dev/null 1> HG18_ref_YH.out 2> HG18_ref_YH.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_YH_encode.txt HG19_ref_YH/HG19_ref_YH' </dev/null 1> HG19_ref_YH.out 2> HG19_ref_YH.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_YH_encode.txt HG38_ref_YH/HG38_ref_YH' </dev/null 1> HG38_ref_YH.out 2> HG38_ref_YH.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_YH_encode.txt KO131_ref_YH/KO131_ref_YH' </dev/null 1> KO131_ref_YH.out 2> KO131_ref_YH.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_YH_encode.txt KO224_ref_YH/KO224_ref_YH' </dev/null 1> KO224_ref_YH.out 2> KO224_ref_YH.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_YH_encode.txt HuRef_ref_YH/HuRef_ref_YH' </dev/null 1> HuRef_ref_YH.out 2> HuRef_ref_YH.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_KO131_encode.txt HG17_ref_KO131/HG17_ref_KO131' </dev/null 1> HG17_ref_KO131.out 2> HG17_ref_KO131.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_KO131_encode.txt HG18_ref_KO131/HG18_ref_KO131' </dev/null 1> HG18_ref_KO131.out 2> HG18_ref_KO131.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_KO131_encode.txt HG19_ref_KO131/HG19_ref_KO131' </dev/null 1> HG19_ref_KO131.out 2> HG19_ref_KO131.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_KO131_encode.txt HG38_ref_KO131/HG38_ref_KO131' </dev/null 1> HG38_ref_KO131.out 2> HG38_ref_KO131.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_KO131_encode.txt YH_ref_KO131/YH_ref_KO131' </dev/null 1> YH_ref_KO131.out 2> YH_ref_KO131.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_KO131_encode.txt KO224_ref_KO131/KO224_ref_KO131' </dev/null 1> KO224_ref_KO131.out 2> KO224_ref_KO131.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_KO131_encode.txt HuRef_ref_KO131/HuRef_ref_KO131' </dev/null 1> HuRef_ref_KO131.out 2> HuRef_ref_KO131.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_KO224_encode.txt HG17_ref_KO224/HG17_ref_KO224' </dev/null 1> HG17_ref_KO224.out 2> HG17_ref_KO224.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_KO224_encode.txt HG18_ref_KO224/HG18_ref_KO224' </dev/null 1> HG18_ref_KO224.out 2> HG18_ref_KO224.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_KO224_encode.txt HG19_ref_KO224/HG19_ref_KO224' </dev/null 1> HG19_ref_KO224.out 2> HG19_ref_KO224.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_KO224_encode.txt HG38_ref_KO224/HG38_ref_KO224' </dev/null 1> HG38_ref_KO224.out 2> HG38_ref_KO224.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_KO224_encode.txt YH_ref_KO224/YH_ref_KO224' </dev/null 1> YH_ref_KO224.out 2> YH_ref_KO224.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_KO224_encode.txt KO131_ref_KO224/KO131_ref_KO224' </dev/null 1> KO131_ref_KO224.out 2> KO131_ref_KO224.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HuRef_ref_KO224_encode.txt HuRef_ref_KO224/HuRef_ref_KO224' </dev/null 1> HuRef_ref_KO224.out 2> HuRef_ref_KO224.err

nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG17_ref_HuRef_encode.txt HG17_ref_HuRef/HG17_ref_HuRef' </dev/null 1> HG17_ref_HuRef.out 2> HG17_ref_HuRef.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG18_ref_HuRef_encode.txt HG18_ref_HuRef/HG18_ref_HuRef' </dev/null 1> HG18_ref_HuRef.out 2> HG18_ref_HuRef.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG19_ref_HuRef_encode.txt HG19_ref_HuRef/HG19_ref_HuRef' </dev/null 1> HG19_ref_HuRef.out 2> HG19_ref_HuRef.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c HG38_ref_HuRef_encode.txt HG38_ref_HuRef/HG38_ref_HuRef' </dev/null 1> HG38_ref_HuRef.out 2> HG38_ref_HuRef.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c YH_ref_HuRef_encode.txt YH_ref_HuRef/YH_ref_HuRef' </dev/null 1> YH_ref_HuRef.out 2> YH_ref_HuRef.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO131_ref_HuRef_encode.txt KO131_ref_HuRef/KO131_ref_HuRef' </dev/null 1> KO131_ref_HuRef.out 2> KO131_ref_HuRef.err
nohup bash -c '/usr/bin/time -v ./iDoComp.run c KO224_ref_HuRef_encode.txt KO224_ref_HuRef/KO224_ref_HuRef' </dev/null 1> KO224_ref_HuRef.out 2> KO224_ref_HuRef.err
