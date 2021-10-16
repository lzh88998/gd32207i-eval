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

#ifndef AWS_TEST_TCP_H
#define AWS_TEST_TCP_H

/* Non-Encrypted Echo Server.
 * Update tcptestECHO_SERVER_ADDR# and
 * tcptestECHO_PORT with IP address
 * and port of unencrypted TCP echo server. */
#define tcptestECHO_SERVER_ADDR0         192
#define tcptestECHO_SERVER_ADDR1         168
#define tcptestECHO_SERVER_ADDR2         137
#define tcptestECHO_SERVER_ADDR3         1
#define tcptestECHO_PORT                 ( 9000 )

/* Encrypted Echo Server.
 * If tcptestSECURE_SERVER is set to 1, the following must be updated:
 * 1. aws_clientcredential.h to use a valid AWS endpoint.
 * 2. aws_clientcredential_keys.h with corresponding AWS keys.
 * 3. tcptestECHO_SERVER_TLS_ADDR0-3 with the IP address of an
 * echo server using TLS.
 * 4. tcptestECHO_PORT_TLS, with the port number of the echo server
 * using TLS.
 * 5. tcptestECHO_HOST_ROOT_CA with the trusted root certificate of the
 * echo server using TLS. */
#define tcptestSECURE_SERVER             1

#define tcptestECHO_SERVER_TLS_ADDR0     192
#define tcptestECHO_SERVER_TLS_ADDR1     168
#define tcptestECHO_SERVER_TLS_ADDR2     137
#define tcptestECHO_SERVER_TLS_ADDR3     1
#define tcptestECHO_PORT_TLS             ( 443 )

/* Number of times to retry a connection if it fails. */
#define tcptestRETRY_CONNECTION_TIMES    6

/* The root certificate used for the encrypted echo server.
 * This certificate is self-signed, and not in the trusted catalog. */
static const char tcptestECHO_HOST_ROOT_CA[] = "-----BEGIN CERTIFICATE-----\n"\
"MIIDwzCCAqugAwIBAgIJAKxtRk5vdcVyMA0GCSqGSIb3DQEBCwUAMHgxCzAJBgNV\n"\
"BAYTAlVTMQswCQYDVQQIDAJXQTEOMAwGA1UEBwwFUGxhY2UxDTALBgNVBAoMBHRl\n"\
"c3QxCzAJBgNVBAsMAklUMRQwEgYDVQQDDAt3d3cudGVzdC5jbjEaMBgGCSqGSIb3\n"\
"DQEJARYLbHpoQHRlc3QuY24wHhcNMjExMDEwMDY1OTE1WhcNMjIxMDEwMDY1OTE1\n"\
"WjB4MQswCQYDVQQGEwJVUzELMAkGA1UECAwCV0ExDjAMBgNVBAcMBVBsYWNlMQ0w\n"\
"CwYDVQQKDAR0ZXN0MQswCQYDVQQLDAJJVDEUMBIGA1UEAwwLd3d3LnRlc3QuY24x\n"\
"GjAYBgkqhkiG9w0BCQEWC2x6aEB0ZXN0LmNuMIIBIjANBgkqhkiG9w0BAQEFAAOC\n"\
"AQ8AMIIBCgKCAQEAxCy60JglCrSvgwEn7IKLIVlgAzo3V0wBWhfHdpT2DXrS2M0m\n"\
"vDz8t5726j/jEfl6Sr3W8/ANnvQ3l4UWGqI32Ug8bTetKI4//Oy+K4auZT7N5Byl\n"\
"5qB9/4kFHPle0EY1UCJWFkEbz8cZaRvgTzOcPcstfp6I+Jtp5JjZhVJPaPjrzrmy\n"\
"jGDfQxLQlCDERaKp7tmMECEXfhV+BURpfCTUaFEO9l01jA5jkx2uy21q5G+8Afbo\n"\
"CQo+4gA9wSA+pZygcC02RxQ97IlDhGwLLHXGZz7hLPKxKNaBRuNE7mzQtBe7cUFa\n"\
"mILvMzvVYkFHawAZHiuzAsVsOJWHCcLOeDf88QIDAQABo1AwTjAdBgNVHQ4EFgQU\n"\
"nsgH3v1c2FN/iMkqZ49WcJ1G5RIwHwYDVR0jBBgwFoAUnsgH3v1c2FN/iMkqZ49W\n"\
"cJ1G5RIwDAYDVR0TBAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAgMImJFFieofd\n"\
"jwvkZPRhxyBUTiaVkqXFAeE0W0ani1R468iBndcc9ShQ7gvtA0RH+4JWQ4S8iKXJ\n"\
"ewvlrBlilaMTjp9DfQwKjIfaH6aoQRJkdt4RGm65AgsEHfwH4qAAvc7cDw1RNdbT\n"\
"XKbhjXh+X6APhZ9icqQhngyeO+A6OI/2PPYt4N9g+vMs0bWHa6YecMBn1PzUPpwc\n"\
"Ee4tqT5yVyg3WMIz0xLECsGcLnutvVt2wqhcRNQ0oHwW9AN0cvMaAHxvRHIV7IpK\n"\
"jPAtGN36XUy9M2FKRQSHxYjSofAY0qN1YKI9fnR0JNwcURwSDOtecl1KFvArnADx\n"\
"LLHxv7EczA==\n"\
"-----END CERTIFICATE-----";

#endif /* ifndef AWS_TEST_TCP_H */
