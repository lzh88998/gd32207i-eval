/*
 * FreeRTOS V202012.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * @brief PEM-encoded client certificate.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the certificate that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
//#define keyCLIENT_CERTIFICATE_PEM \
//"-----BEGIN CERTIFICATE-----\n"\
//"MIIDbDCCAlQCCQCYZxBXuhCrZTANBgkqhkiG9w0BAQsFADB4MQswCQYDVQQGEwJV\n"\
//"UzELMAkGA1UECAwCV0ExDjAMBgNVBAcMBVBsYWNlMQ0wCwYDVQQKDAR0ZXN0MQsw\n"\
//"CQYDVQQLDAJJVDEUMBIGA1UEAwwLd3d3LnRlc3QuY24xGjAYBgkqhkiG9w0BCQEW\n"\
//"C2x6aEB0ZXN0LmNuMB4XDTIxMTAxMDA3MDA0N1oXDTIyMTAxMDA3MDA0N1oweDEL\n"\
//"MAkGA1UEBhMCVVMxCzAJBgNVBAgMAldBMQ4wDAYDVQQHDAVQbGFjZTENMAsGA1UE\n"\
//"CgwEdGVzdDELMAkGA1UECwwCSVQxFDASBgNVBAMMC3d3dy50ZXN0LmNuMRowGAYJ\n"\
//"KoZIhvcNAQkBFgtsemhAdGVzdC5jbjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCC\n"\
//"AQoCggEBAJisOeyHYbXtAnLGcv0qfDKvRhbAJyK+YCTWKBvX3pStR/gyU7Gl5WsK\n"\
//"Xwwz4GlpSr4N3xLsMzt/2OqPXPyjqUBuJJ7t8Pj0K4rmD1Ky8sejccaiazSxdQEo\n"\
//"W7UVYa2UGoW6jmlNxt0i0jLTNoPtj+1IYi3nTLDrVDybn2VfIQDrXgPHtZ/BA7i7\n"\
//"xHclKgjauXmr+A/lc6QUTStUQeo/ySQWyHkTV48P4xhKvPN9KskA9CfEchtlf/Sr\n"\
//"MtStuOg0dS5SyFF4Ou/Phsjar8QPd9A/8VyjcqVUFcts1XD2MD2WmsnT1ov2Kzi8\n"\
//"4+Y83Gk1UbLpqJ9gLmWTEodRFhHHZ2MCAwEAATANBgkqhkiG9w0BAQsFAAOCAQEA\n"\
//"LTUFcX0CysaMfMxZPov/KgQ/g1KFOVpglsXjHfeY0oNQ07MxLEQ9B6diNQyUiMld\n"\
//"7BkiTMDw8hNsSoUhU4b/eTyoucI3F+y10iRIgKwq6TZrdoEVSrGD+CS2V2o5oyZH\n"\
//"JlYOdxnVDmFeZLl6Ic5JcQRbeTcQUKSK0sI8PUTrneyZApB6QpuD7QNcwBgaWXZe\n"\
//"IvRroceF57odp7vPlxLhDUt6m8pg7x4u5Z76E9SoLunePBqZY0KrBDs0HtZpGOog\n"\
//"UNL+QEZkHMSp1SAIt/mixZNFE+VLJlS+C4E62tzfhNmlzImNfrcyczjiv6Sfdp0+\n"\
//"Q2oIeOQYmwY1Fs6yZq9tuw==\n"\
//"-----END CERTIFICATE-----"
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAL8mSF+xFp59XHlhA/BzHz0H5bv/MA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTEwMTEwNDA1\n"\
"NDhaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCs7f7JkmlK5A2E+O+2\n"\
"qjFhqicQHpyurZnkhLDFKBtHxQ8v5BbA9LuOHQeWa/ksVLkdC2QqcEJgi70PPGVd\n"\
"mrhpWIq4MmE1wfCXW8tDFnjKyDMqFwUHjG8wMX37RfM5vNKQYBMAQ1w6Z7dB0iCn\n"\
"3kIc6XH4WrmSvdIX3KFh0jDqc0JfMkIcAWD1vAdgi8jhkZmS2suHJvftgDZY9TWa\n"\
"EMyPzLKDgocIJ17751n8WVKnezxfjxD3GGYYGMQBFS4O2HP+hFpW2/GGwESXaJxz\n"\
"YFp7o2Gh7Lr4XOYRq83oCyVOZAkJRmAapWmMjQ9Sy1qEjE7nXAC6SnkEToxK4L0+\n"\
"tl6TAgMBAAGjYDBeMB8GA1UdIwQYMBaAFFZL/Ze7hI+vow2eHvacDu7w+xCvMB0G\n"\
"A1UdDgQWBBSXfVRy3Rh7qF0IA7XH62k4j+r/sjAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAYNUuJVQxs9Wa9ijP50aQY8Qu\n"\
"23MAtjGAsIdH9+dV78nY16SF6JSq7L1xM/zRgYfV809sFmb02urJjc3mZ3MuFZxu\n"\
"gvY1iYK8jGuOlS6OUqvALdqLmQ5uzHvka8SAoxH4RjWuchfiClJz+llcdKSxcaa7\n"\
"HWaWdYFVljsWVT2KUvBWdEnOI2sOMCgLTLjcU20atOb9sbinTgSnQJsB2jmpDVFF\n"\
"QC0pM16LrQM92twd6MOS2Pidt8yAUBW0aW1/VJc/5s8CJqSRWAGnzE0zdiBzunES\n"\
"oK06+uTzSsd7a43Hzxf84ngaI+pkwr18QnZaYALquIaxOmV86TzAHTSdUQSrdQ==\n"\
"-----END CERTIFICATE-----"
//#define keyCLIENT_CERTIFICATE_PEM \
//"-----BEGIN CERTIFICATE-----\n"\
//"MIIDWjCCAkKgAwIBAgIVALNwEuIEXofizlgFPSi4o2QHbsMgMA0GCSqGSIb3DQEB\n"\
//"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
//"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMTEwMTExMTAx\n"\
//"MjFaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
//"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC7Gm1Ps+caajlLl98s\n"\
//"+3Ts9rgUxJ2friIDqcPqh/ywq5bxMMt0QxVrMLVw+eeIxKNtWXJsgCRE0GdduciI\n"\
//"9G26bEc7FbSQ0urX6nlFsUer5RIz8Jf2tXR0hC8/mUUbgrJ2+of+Th75ei99y59M\n"\
//"3z+nLk+uqbqJCai+Ks9iGFBNdG1j8P8edNa/eyt1FAd1knN+BDygtHHktI3Bvnah\n"\
//"ghlf2a/1nL1FNJ4osnDkP7mS10cBszqBcodYALHKk2eFA3iS+JrqoKK05eIpa+Xv\n"\
//"yXOzms2DmldrNgb1Sxf+p9vFpB+XowqlzNPyMEPQVsVWAA4DbJ10Z9YvN3Xjsyxn\n"\
//"DYS/AgMBAAGjYDBeMB8GA1UdIwQYMBaAFEnjP2+AafSEMtN7yy3en1YHvOtWMB0G\n"\
//"A1UdDgQWBBTfPkwNVdMCgEVR7kMpkQT3qncTHDAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
//"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEASLZT0fjtG/xmldOfOMx7+sg0\n"\
//"iRQka2/fTX8HMVMkrRG/BGukaXW/Kcaxx8B7xJU7fdDy450UZLVEn+3uyGCIXMHA\n"\
//"wMj//06LVD7yHALghpO5jKlVeX+q+9M+9pjgQSQwMl4Qx+3ODgI1dPnvTodyW+qC\n"\
//"1pOLr/zi+MsD/FP1ae6XW+xXxNkVxG8ZtcYqKgx5Zp2MzG3RCgmQecMy8SwcDp7Y\n"\
//"+S2xeISe36UnXKmLCrziDlKYYF/UJNL/Eg9X3KaVTyNmQj3GVhuk/9tT7lhqjowK\n"\
//"pxT8SqIKS0gVGaV73g84pAoKEcckVtsy43RxrSmlzTFjLIvICXX1ZODj/ZeDaQ==\n"\
//"-----END CERTIFICATE-----"
/*
 * @brief PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 *
 * @todo If you are using AWS IoT Just in Time Registration (JITR), set this to
 * the issuer (Certificate Authority) certificate of the client certificate above.
 *
 * @note This setting is required by JITR because the issuer is used by the AWS
 * IoT gateway for routing the device's initial request. (The device client
 * certificate must always be sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM    NULL

/*
 * @brief PEM-encoded client private key.
 *
 * @todo If you are running one of the FreeRTOS demo projects, set this
 * to the private key that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
//#define keyCLIENT_PRIVATE_KEY_PEM \
//"-----BEGIN RSA PRIVATE KEY-----\n"\
//"MIIEpAIBAAKCAQEAmKw57Idhte0CcsZy/Sp8Mq9GFsAnIr5gJNYoG9felK1H+DJT\n"\
//"saXlawpfDDPgaWlKvg3fEuwzO3/Y6o9c/KOpQG4knu3w+PQriuYPUrLyx6NxxqJr\n"\
//"NLF1AShbtRVhrZQahbqOaU3G3SLSMtM2g+2P7UhiLedMsOtUPJufZV8hAOteA8e1\n"\
//"n8EDuLvEdyUqCNq5eav4D+VzpBRNK1RB6j/JJBbIeRNXjw/jGEq8830qyQD0J8Ry\n"\
//"G2V/9Ksy1K246DR1LlLIUXg678+GyNqvxA930D/xXKNypVQVy2zVcPYwPZaaydPW\n"\
//"i/YrOLzj5jzcaTVRsumon2AuZZMSh1EWEcdnYwIDAQABAoIBAFIYopku/3rddOiV\n"\
//"D/ZU5y42FAFd2G2VY4vLYQv/25+lQkMThO/NHn2duRiNuMnWJavnN6IsQyxmhhUz\n"\
//"fDQaKYQM9kJD/sVQPy3Uoj69HVH+8Mp4Qh+2oQ07T30jfz/gmRZ6B+RWP25gMBnG\n"\
//"e9UbZL6aori+XP3xvX1NzbusGMot8eM56rphMJYpKwicFCWA6P11wHsWfVQ7OSEY\n"\
//"ux9qdFVHhH8DJ64dKOcXgtL/wMCCyk/WW7ucNazBnehs15fb9Mp8hB1Ng2Xqj78o\n"\
//"J6vSdwB4FqPYLKcCVSsoE44cGwdnpq9ChkyOiMRz8yuCGvgDraMImZMyYo7+ZY+D\n"\
//"fDh19RkCgYEAx1NdeUP5hYxuIGkWhP3TL9WpsN1ijtCb5CH8ezEB1Pg4MUULz7hz\n"\
//"T8qHlCALhOajljGF5v0tocsTiGsoeoc7gk1/WfHp/an9+MjSgKYclWgvf14ZiRFx\n"\
//"mKNp6ZtQC+2g1QanEeb+BToaxGjb/YnqxkeNLMms62fcgddfz7lWbGcCgYEAxBUQ\n"\
//"FE0bJf1VlicYqBjcNcHq8hrYM84gigORnN2nUQhMJuTSiGNx8tWUTjnYFylKAHV+\n"\
//"rskrKvXl1sDCRUgyg2mANvDjIbk4EC2FgiestKKE5d/Vgg2kJUqb/RmyIlcLh0EI\n"\
//"tibP4VcVxdpHcw/4us5oZmRin3KpMAlwGoGKj6UCgYEAxaQEwFRFW0WWgO6SlMX2\n"\
//"HK04eBXcPw3cNYX5itFaJqkFVt1Gy+3x8ME6VAa+RUZIGIn8YsDR+WaadJ8EYRIs\n"\
//"UJS1XSNBR/PBz2iZSVTsbL0Es79DhKTWRWprf2YwJdO2sOPKzzaC0/38QppS4ABb\n"\
//"2cVi13EV08mFXP2IlDkK16sCgYEAlTLdsETXcnmoRP9ssINyE+mA50Vr20dt1PZQ\n"\
//"Nwclh/ADWdjlJWhdzQOcvEUhWsZNC7pbcY2ari66+0RizirYXMvLBoMWoJN5yD2L\n"\
//"B/U+YZgD/ZHquPG+Q63YsaZ6t8x59imTAl7X8MO9ynWDxlaR0Tq7j6W0sVSize1w\n"\
//"goqtLw0CgYAmsk+JAngeN2QFPCnscsIpJukUOwo9pW8OO7F9oFxf+cGTfqhrzixE\n"\
//"BMfdXmiKGLwIIcbCsAkMGtVvz7rPsnX4dTM1sVUY3iG/cTxZJYjOdFwsp4H33/Rm\n"\
//"O6vg6nc1R6+mUVcKTFmkKO1GkVUKSHCQ8kFFNTOms/id9nRhKrQaaw==\n"\
//"-----END RSA PRIVATE KEY-----"
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEogIBAAKCAQEArO3+yZJpSuQNhPjvtqoxYaonEB6crq2Z5ISwxSgbR8UPL+QW\n"\
"wPS7jh0Hlmv5LFS5HQtkKnBCYIu9DzxlXZq4aViKuDJhNcHwl1vLQxZ4ysgzKhcF\n"\
"B4xvMDF9+0XzObzSkGATAENcOme3QdIgp95CHOlx+Fq5kr3SF9yhYdIw6nNCXzJC\n"\
"HAFg9bwHYIvI4ZGZktrLhyb37YA2WPU1mhDMj8yyg4KHCCde++dZ/FlSp3s8X48Q\n"\
"9xhmGBjEARUuDthz/oRaVtvxhsBEl2icc2Bae6Nhoey6+FzmEavN6AslTmQJCUZg\n"\
"GqVpjI0PUstahIxO51wAukp5BE6MSuC9PrZekwIDAQABAoIBAE6PjHlsf1MbiZzI\n"\
"LrawWODCmR50mb+tdEVhlqDq2IHhX0XlfATK6c3lGEZY5QkjsDkmrKmu+Ci+MvSR\n"\
"/obovDB3ngWSNaFjavaIKC5hLh0JmFzdulY0kWq2gUI/BAFN6+bVDqzG7UZHSfSo\n"\
"DlfU2/ogf7tRFA87Fw/qFpLHF5vaYwb253YKyrPDCAiJNHiPXiqfvAcZ0KI/eOrc\n"\
"tJheiuT8z9OMH6VyKQ0Q8HpUpYQZorVxacAttkMl6hvV6978Yv5TJUXNqBZ/XIR0\n"\
"/fL5Y90IeegyDNRgtJtCGT/N7JSTkufu4hH4WY371Psd9pj8LVJWv3W7vCbgsZxE\n"\
"fdHLs7ECgYEA5QqJjR7AeZOQzaMMkxXe/T4OwAeAGN0AAi02hMynLhIju1bucbnZ\n"\
"oK1+XLohS21FT/AkBY0KfN+NRWkuI+rcOLQ+uVyGptaIRhQk8HGG3u4EAIUr1O2C\n"\
"+GWPu6200TfLjeEJWWkqri4K8dKVpiuX5qDIs2dzrtig8ZQntDFt+tkCgYEAwUi1\n"\
"NJTQtKGIX6vk2gkgQn7K3rPR1MnxA2gQ3I8ZTJqSAmi96aoEDQXL+CYeRM17jhWZ\n"\
"J/bmkc+QyfXfxJSSCHNGywZCfyDuZE1W5PjNFcvSCHLQsZJBEyuTJWCZPOTjEWjm\n"\
"boL1X/lWExauon9ma13eK4Tn4mMUNG12rkjmSUsCgYAyuybEby9KvniwU5ERcyK1\n"\
"DO3PctnYp/q8gK82su3Espffgt3FqtidUlBO0ZtWTZmwnwwbfqX4CrwLx8REiFzG\n"\
"4oWSIQBiK9p7SzLzXvH0ptuUEesneoQr6LLxawRF4wnfHx0nBLhDZEdgULh82eMH\n"\
"Xk2WDy/8ZlcfqyUwMFKf4QKBgH8/aNzHJGfm+KtTtYS+AVkFtHXNmNUoZd3CQ2eR\n"\
"ZiyCjqG7Z1xQK/6O1Gv4XHEbfr5aBczDxaQ1LLNphfobfdDGY9MBugGMIqYyLITu\n"\
"L8aruwkI3dAp42HFjEhNQlVOsxchIqOa4ARhWIOUqUAd88W3tK6d/zOR2xlw/3Na\n"\
"VxHlAoGAWrepyGPRtQa4WrR6fmqCa5sE5fSqSRMFLDovXeaBKOmbcuQnAhK85GD5\n"\
"ouP+zQGFt1G42oS4TlNyQIaDrS6ow3DNiPB43KoYYn26qlvJIUHA4a60C2x9bVv3\n"\
"iIPo4C6D9J09/GGTnpPTDOjSMv2h2Q4S+3Pdqe+5vGrNqXYcinM=\n"\
"-----END RSA PRIVATE KEY-----"
//#define keyCLIENT_PRIVATE_KEY_PEM \
//"-----BEGIN RSA PRIVATE KEY-----\n"\
//"MIIEpQIBAAKCAQEAuxptT7PnGmo5S5ffLPt07Pa4FMSdn64iA6nD6of8sKuW8TDL\n"\
//"dEMVazC1cPnniMSjbVlybIAkRNBnXbnIiPRtumxHOxW0kNLq1+p5RbFHq+USM/CX\n"\
//"9rV0dIQvP5lFG4KydvqH/k4e+XovfcufTN8/py5Prqm6iQmovirPYhhQTXRtY/D/\n"\
//"HnTWv3srdRQHdZJzfgQ8oLRx5LSNwb52oYIZX9mv9Zy9RTSeKLJw5D+5ktdHAbM6\n"\
//"gXKHWACxypNnhQN4kvia6qCitOXiKWvl78lzs5rNg5pXazYG9UsX/qfbxaQfl6MK\n"\
//"pczT8jBD0FbFVgAOA2yddGfWLzd147MsZw2EvwIDAQABAoIBAQCVSufwEeeUby/a\n"\
//"fotIdDh/H/oQMDZphGOFsr8t82YQfkoJl9qvoRuFFS+hvvYdbnHMvfOMWc8WzYe9\n"\
//"BJHbndW0S9OmdJJIgNN8h45Oqr86jKSypwZKh80tb4/X2m+HHQlT4GIE68bRX8pn\n"\
//"QMOSbgx3VH+mKa46zGdFnhkt96KTubPbIIBSk6Npq+ninXPY0xaulw+X16fp8aN/\n"\
//"ptS7gIg8uDMcRyb97TOCPLUc8sLXP5QqzqWjywOiAayILDexQKi6i+pYervJzBqs\n"\
//"ePbNJOhWkmlrqJaCxgLnLCPfsc7r+PJfJOkvcJMwzb4Z8kfDU5RmgwrSXHnBr209\n"\
//"LRzCg24JAoGBAPfYr6ijKE2dvJOyz0zFh0sefW+O1iR7gmDnX+O5Wknc5jf0G5MZ\n"\
//"z8AlD0oKHkAvxD37niuaH34WIR6YQeFk3+LiIG45Ry/3+rIiKbATReksXkkAQ3y8\n"\
//"+KrePUU+jnCkj1IAxkGYmQqyU6XCZvoYDeQM2SKe5AOApOEFvf14+nh1AoGBAMFC\n"\
//"LG6Oqm0nDfSv+i2tMdllTzT6I4Gajfap0vjb15CgsGQ9jScH9uIKgnA49kM/ad1U\n"\
//"YHTXHfjJ7Wgx/x+n2uMCWyswG6atMeVTQM3WJq+auMAmS6XJty0E3LTfvszFWaRO\n"\
//"H7NCkHgrH/NSHUZDQsJ/GrTVeCvO+FWuzrrDA0HjAoGBAJveqppkAfTOPsqkqbqe\n"\
//"f3e+tSRzsDlBc719xdBxwVaylhaabr0UfpNYu0TVGDFF2SUiGVdSlnu1bx7OoqAd\n"\
//"0K/fhoXLf/mq+v8MfSs+87ixLpq6j7bjIYBURDRII0y0MW5hDk4yqg0QGYslt52R\n"\
//"gyro6aXcR4nsXcUm11WRv/QBAoGAHlQxPuR60Ih5gzX+0B5HHXPtu0WqPtOvhc9f\n"\
//"AZkWumbNZ93VAhQY5Z56m/wEgcc46Pgt7wg3duzRqjF2dVRVYJzlC+EP5dd2ZiPr\n"\
//"nqIGDjb82YLpCkqeyZziuiwG+IHcMJHmHa7Ll2BFMl1npLg3iOiDm2+I3W8sv92g\n"\
//"KeUi5LsCgYEAzmCMAGg+9QkG/bnVXkaKDFZjgkB1AlFIcAvpPpWoUp2g8wkQSG73\n"\
//"fP7tnfWd6EMbIpF8Eov+U7Z59Q8qwpXgCYcwGSriIlLt9UiZurX05Y92HGO51rMu\n"\
//"uLs3Bxfxv/YGIz19ny5qij35gKUuNu3RA7Ip5yOhwYX75JF9M318umk=\n"\
//"-----END RSA PRIVATE KEY-----"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
