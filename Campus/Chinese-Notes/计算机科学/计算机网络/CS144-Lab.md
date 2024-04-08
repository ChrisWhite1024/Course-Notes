# Checkpoint  0
## Networking by hand
### Fetch a Web page
```bash
cs144@vm:~$ telnet cs144.keithw.org http
Trying 28.0.1.106...
Connected to cs144.keithw.org.
Escape character is '^]'.
GET /hello HTTP/1.1
Host: cs144.keithw.org
Connection: close

HTTP/1.1 200 OK
Date: Mon, 18 Dec 2023 09:29:05 GMT
Server: Apache
Last-Modified: Thu, 13 Dec 2018 15:45:29 GMT
ETag: "e-57ce93446cb64"
Accept-Ranges: bytes
Content-Length: 14
Connection: close
Content-Type: text/plain

Hello, CS144!
Connection closed by foreign host.
```
### Send yourself an email
```bash
cs144@vm:~$ telnet smtp.qq.com 25
Trying 198.18.14.46...
Connected to smtp.qq.com.
Escape character is '^]'.
220 newxmesmtplogicsvrszc5-1.qq.com XMail Esmtp QQ Mail Server.
HELO qq.com
250-newxmesmtplogicsvrszc5-1.qq.com-11.137.104.98-53488688
250-SIZE 73400320
250 OK
AUTH LOGIN
334 VXNlcm5hbWU6
Y2hyaXN3aGl0ZTMzMzMzQHFxLmNvbQ==
334 UGFzc3dvcmQ6
anlucnpjb3JwYmF4YmpqYg==
235 Authentication successful
MAIL FROM: <chriswhite33333@qq.com>
250 OK
RCPT TO: <moe@wh1te.dev>
250 OK
DATA
354 End data with <CR><LF>.<CR><LF>.
From: "Chris" <chriswhite33333@qq.com>
To: "White" <moe@wh1te.dev>
Date: Tue, 15 Nov 1994 08:12:31 GMT
Subject: D-Mail

El Psy Kongroo
.
250 OK: queued as.
QUIT
221 Bye.
Connection closed by foreign host.
```

```
Return-path: <SRS0=Z8Bj=5h=qq.com=chriswhite33333@wh1te.dev>

Original-recipient: rfc822;chriswhite1024@icloud.com

Received: from st43p00im-qukt05021701.me.com by p44-mailgateway-smtp-778464bd6-glqrh (mailgateway 2403B92)

with SMTP id d888ea55-3ef2-4d3c-b43b-1fafd97034a9 

for <chriswhite1024@icloud.com>; Mon, 18 Dec 2023 10:56:29 GMT

X-Apple-MoveToFolder: INBOX 

X-Apple-Action: MOVE_TO_FOLDER/INBOX

X-Apple-UUID: d888ea55-3ef2-4d3c-b43b-1fafd97034a9

Received: from i-bf.email.cloudflare.net (i-bf.email.cloudflare.net [104.30.8.15])

by st43p00im-qukt05021701.me.com (Postfix) with ESMTPS id EC1AC39C0207

for <chriswhite1024@icloud.com>; Mon, 18 Dec 2023 10:56:23 +0000 (UTC)

X-ICL-SCORE: 3.333033230041

X-ICL-INFO: GAtbVUseBVFGSVVESgMGUkFIRFcUWUIPAApbVRYSFhEAREQZF15TQFUcAkpaY2QxRUQ8TzpaC1cd

 RBcGVlNZD0gaDgURQ0EKHA0DREsDBVE1Dg5GDFUYBhAPRFceVAtABAhIFBddFEIGEBZKWgEGVltK

 VllAHgdXV1kOEhRfC0AcVAQRVlVbAxwVSBQUX0MGExUHBR0eWAcBW0YHDEILQBxUBBFWVVsDHBVI

 FBRfQwYTFQcFHR5YBwFbRhMcDRQTBFcFGBUSFg8cHVtVRERTDBYcCAMnCARSTUBWQ0oGAlY0TlU1

 TXUHI0c8JzQ8BgBaNEFfQDoGD1I0ORcGVlNZD0tbRgUbDRQBHQsPBA9YXxYQSFZFTHBfARkWExNW

 U1kPVw==

Authentication-Results: bimi.icloud.com; bimi=none

X-ARC-Info: policy=fail; arc=none

Authentication-Results: arc.icloud.com; arc=none

Authentication-Results: dmarc.icloud.com; dmarc=pass header.from=qq.com

X-DMARC-Info: pass=pass; dmarc-policy=quarantine; s=r0; d=r1; pdomain=qq.com

X-DMARC-Policy: v=DMARC1; p=quarantine; rua=mailto:mailauth-reports@qq.com

Authentication-Results: dkim-verifier.icloud.com;

dkim=pass (1024-bit key) header.d=qq.com header.i=@qq.com header.b=SB8S0d6H

Authentication-Results: spf.icloud.com; spf=pass (spf.icloud.com: domain of SRS0=Z8Bj=5h=qq.com=chriswhite33333@wh1te.dev designates 104.30.8.15 as permitted sender) smtp.mailfrom="SRS0=Z8Bj=5h=qq.com=chriswhite33333@wh1te.dev"

Received-SPF: pass (spf.icloud.com: domain of SRS0=Z8Bj=5h=qq.com=chriswhite33333@wh1te.dev designates 104.30.8.15 as permitted sender) receiver=spf.icloud.com; client-ip=104.30.8.15; helo=i-bf.email.cloudflare.net; envelope-from="SRS0=Z8Bj=5h=qq.com=chriswhite33333@wh1te.dev"

Received: from out203-205-251-72.mail.qq.com (203.205.251.72)

        by email.cloudflare.net (unknown) id RG92Nrb6R2cD

        for <moe@wh1te.dev>; Mon, 18 Dec 2023 10:56:16 +0000

Received-SPF: pass (mx.cloudflare.net: domain of chriswhite33333@qq.com designates 203.205.251.72 as permitted sender)

receiver=mx.cloudflare.net; client-ip=203.205.251.72; envelope-from="chriswhite33333@qq.com"; helo=out203-205-251-72.mail.qq.com;

Authentication-Results: mx.cloudflare.net;

dkim=pass header.d=qq.com header.s=s201512 header.b=SB8S0d6H;

dmarc=pass header.from=qq.com policy.dmarc=quarantine;

spf=none (mx.cloudflare.net: no SPF records found for postmaster@out203-205-251-72.mail.qq.com) smtp.helo=out203-205-251-72.mail.qq.com;

spf=pass (mx.cloudflare.net: domain of chriswhite33333@qq.com designates 203.205.251.72 as permitted sender) smtp.mailfrom=chriswhite33333@qq.com;

arc=none smtp.remote-ip=203.205.251.72

DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=qq.com; s=s201512;

t=1702896975; bh=YIltfbcPnUjR2iDF7TYlkQguo0BDXv4Pp+kKVEmazgY=;

h=From:To:Date:Subject;

b=SB8S0d6HKTkBuOOKpazOlU+BcdTzNRwhkk1LzQLOEGMhykNOdSHRmMSVVsUk5DXDn

ODM2YIddxNO0+qWsAkfAWXErIILRDtGE0I7zc0pvJb1OrP/CQMLah+4/sEOL49Cf7r

k3g0L5Os+/NzT7gzvWdnk7ybXVsmzSfTGDZc6hTc=

Received: from qq.com ([36.23.158.126])

by newxmesmtplogicsvrszc5-1.qq.com (NewEsmtp) with SMTP

id C51B3EE9; Mon, 18 Dec 2023 18:49:17 +0800

X-QQ-mid: xmsmtpt1702896631trc82r92i

Message-ID: <tencent_82089042644A73B5E1A2EACD668A897B690A@qq.com>

X-QQ-XMAILINFO: McFs54YitxxBIdwCgTW4+cfpas7PkBzGjg++In8qgXlh7PZirAAMPK7jVi0C/q

CXVstOv+9olxxNLY1Ou50ZiB0R993ieZFAx+f9KBnIzMZ5pmFUYZwV7RIOdC8tV0FL3wsEXncqUY

dCVSrU8lJAjgRlyPwOmUZN/OqHy5RIXBew85ILX84jF3qdDv+TFSJFljHFJPKz0RWISG6O0Z6w8q

1xPWb5mh7puNgw51rKaCNfiq8vPB4oQNZuBOARxJHtK3oFDtDSzc8iFxv56TfFNkrRcfIZjQJIdz

ntJIaqO1o49CT98HZWfDoBcMRIAjOMkMlL3rW9N6mhUBnVwTS3XVILRlyMI988Mv+tFewbEswm1F

RyhwVTgqYEJXLjeOF1vz4r1RjI1/oPqEaA3t+Y1AsVoeo22aaCYRIFUzEw4vOVigBx20de8h2oYm

h1wIPKhAsAGXmykr95u9yaNq+bQHmzE7gSLOVFrBXU+XQOYLAqc0ZpmNJoEtIXrOoci3QQ0G6avL

EG5BA9sGedKKXB15QJ5GCN/jUtR2dvHZSKWiEp/2neI/dxup/R8Z4km30m0zcaJi52RuQzPaOy1Q

wJM5TFgWUPf6WbfsSZ90/ZUxsRtcAcwjOoPK9S12tvxk6ekk5G0JK0LuJaIsUBNRoA9l8TQWA3m1

3m+LF8+YNx+uaivE53IQ6QNNRhlgJg8No6iSKxNPQbvnaZ+KVr6Efe/OH6yAupqswgpEjkHNN5CZ

yqy41TX5Ia3CugV5a7VjWAHqlLA5lE0LcrLi7ueGzTztXUzqcaadGlZvm7gIwMBge5tSBKRdpmcr

aTnxVCJRPL4JrQVF+X5ulgJFE4M1cH/jH9SZX0f9LXNM5f/nx62ixm/+PcT2zXI30TR0LS3p91zl

CbfYKeb+xZLKsRkbn+J15IORWEawzCmzdMTKc+MuvePf3rihjZtsSzybMd5eFPOk1ozPiCtsgYlr

No0jdK2LkeLIQ7OYT3LQ==

X-QQ-XMRINFO: M/715EihBoGSf6IYSX1iLFg=

From: "Chris" <chriswhite33333@qq.com>

To: "White" <moe@wh1te.dev>

Date: Tue, 15 Nov 1994 08:12:31 GMT

Subject: D-Mail

X-CLX-Shades: None

X-MANTSH: 1TFkXHRsRCllEF2VQe01+fVIbUBpkEQpZTRdkRURPEQpZSRcTcRsGGx13Bh4ZBho

 GGgYYGgYacRoQGncGGgYaBhoGGgYaBhpxGhAadwYaEQpZXhdsbHkRCkNOF3BQTB9ibU99Yl9AQ

 HAdfEx/bBNzRE9CeEJIGE17UEsHEQpYXBcZBBoEHxoFGxoaBBIYBB4YBBkaEBseGh8aEQpeWRd

 JXklEGhEKTVwXHhoRCkxaF2hlTW9rEQpNThdoaxEKTEYXb2tNbhEKQ1oXGBoZBBgaHwQYHxsEH

 RgRCkJeFxsRCkJcFxsRCl5OFxsRCkJLF2Z9ZUdjZnlaQRhfEQpCSRdmfWVHY2Z5WkEYXxEKQkU

 Xa0IcHkldZR55GWcRCkJOF2Z9ZUdjZnlaQRhfEQpCTBdsWWYfWFpZe00ZXhEKQmwXZkhDeWxif

 kFpU08RCkJAF20YHn4bYVsZX1tiEQpCWBdueGJYHm9IQk8aXhEKTV4XBxsRClpYFxkRCnBoF2l

 uZkFuSB9aZ2hZEAcZGhEKcGwXY1hiS2Zcb2BdfhgQBxgbEQpwQxdiHE9sU34TZHgaHBAHGRoRC

 m1+FwcbEQpYTRdLEQ==

X-Proofpoint-ORIG-GUID: Zzf5HGeWHujjZ7VfUF9YnehRhb2gQza-

X-Proofpoint-GUID: Zzf5HGeWHujjZ7VfUF9YnehRhb2gQza-

  

El Psy Kongroo
```

![[Pasted image 20231218190807.png]]

### Listening and connecting
```bash
cs144@vm:~/cs144-computer-network$ netcat -v -l -p 9090
Listening on 0.0.0.0 9090
Connection received on localhost 33278
Hello
Hello
El Psy Kongroo
^C
```

```bash
cs144@vm:~/cs144-computer-network$ telnet localhost 9090
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Hello
Hello
El Psy Kongroo
Connection closed by foreign host.
```

## Writing a network program using an OS stream socket
### Modern C++: mostly safe but still fast and low-level

### Writing webget
```cpp
void get_URL( const string& host, const string& path )
{
  cerr << "Function called: get_URL(" << host << ", " << path << ")\n";

  const std::string service = "http";
  const Address addr( host, service );
  TCPSocket socket;
  socket.connect( addr );
  std::cout << "Peer Address: " << socket.peer_address().to_string() << "\n";
  std::cout << "Local Address: " << socket.local_address().to_string() << "\n";

  const std::string http_request = "GET " + path
                                   + " HTTP/1.1\r\n"
                                     "Host: "
                                   + host
                                   + "\r\n"
                                     "Connection: close\r\n\r\n";
  std::string http_response, buffer;
  socket.write( http_request );
  while ( !socket.eof() ) {
	/* 
	 * 由于 FDwrapper 中 non_blocking_ 被初始化为 false 
	 * 如果无数据可读 read 函数会被阻塞，直到有数据可读才返回
	 * 直到 read 函数返回 0 FDwrapper的 eof_ 才被置 1
	 */
    socket.read( buffer );
    http_response += buffer;
  }

  socket.close();

  std::cout << http_response;
}
```

```bash
cs144@vm:~/cs144-computer-network$ cmake --build build --target check_webget
Test project /home/cs144/cs144-computer-network/build
    Start 1: compile with bug-checkers
1/2 Test #1: compile with bug-checkers ........   Passed    0.27 sec
    Start 2: t_webget
2/2 Test #2: t_webget .........................   Passed    0.95 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   1.24 sec
Built target check_webget
```

## An in-memory reliable byte stream
```cpp
class ByteStream
{
protected:
  uint64_t capacity_;
  uint64_t bytes_pushed_ = 0;
  uint64_t bytes_poped_ = 0;
  bool eof_ = false;
  bool closed_ = false;
  bool error_ = false;
  std::string buffer_; // 需要在构造函数初始化列表中初始化
// ......
```

```cpp
ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ), buffer_() {}

// 如果 data 超过 available capacity 就仅传输 available capacity 大小的数据
void Writer::push( string data )
{
  uint64_t available = available_capacity();
  if ( data.size() > available ) {
    // throw runtime_error("ByteStream don't have enough capacity");
    data.erase( available, data.size() - available );
  }

  buffer_ += data;

  // cout << "Successfully push: " << data.size() << " Bytes of data\n";
  bytes_pushed_ += data.size();
}

void Writer::close()
{
  eof_ = closed_ = true;
}

void Writer::set_error()
{
  error_ = true;
}

bool Writer::is_closed() const
{
  return closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - static_cast<uint64_t>( buffer_.size() );
}

uint64_t Writer::bytes_pushed() const
{
  return bytes_pushed_;
}

string_view Reader::peek() const
{
  string_view string( buffer_.begin(), buffer_.end() );
  return string;
}

bool Reader::is_finished() const
{

  return closed_ && buffer_.empty();
}

bool Reader::has_error() const
{
  return error_;
}

void Reader::pop( uint64_t len )
{
  buffer_.erase( 0, len );
  bytes_poped_ += len;
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}

uint64_t Reader::bytes_popped() const
{
  return bytes_poped_;
}
```

```bash
cs144@vm:~/cs144-computer-network$ cmake --build build --target check0
Test project /home/cs144/cs144-computer-network/build
      Start  1: compile with bug-checkers
 1/10 Test  #1: compile with bug-checkers ........   Passed    0.23 sec
      Start  2: t_webget
 2/10 Test  #2: t_webget .........................   Passed    1.23 sec
      Start  3: byte_stream_basics
 3/10 Test  #3: byte_stream_basics ...............   Passed    0.93 sec
      Start  4: byte_stream_capacity
 4/10 Test  #4: byte_stream_capacity .............   Passed    0.93 sec
      Start  5: byte_stream_one_write
 5/10 Test  #5: byte_stream_one_write ............   Passed    0.92 sec
      Start  6: byte_stream_two_writes
 6/10 Test  #6: byte_stream_two_writes ...........   Passed    0.90 sec
      Start  7: byte_stream_many_writes
 7/10 Test  #7: byte_stream_many_writes ..........   Passed    0.96 sec
      Start  8: byte_stream_stress_test
 8/10 Test  #8: byte_stream_stress_test ..........   Passed    0.96 sec
      Start  9: compile with optimization
 9/10 Test  #9: compile with optimization ........   Passed    0.11 sec
      Start 10: byte_stream_speed_test
             ByteStream throughput: 1.98 Gbit/s
10/10 Test #10: byte_stream_speed_test ...........   Passed    0.12 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) =   7.30 sec
Built target check0
```

### `std::string_view`[@sbAnswerWhatString_view2013]
1. `string_view` 提供了对原始字符串的视图，对 `string_view` 使用修改方法不会影响到原始字符串，只是修改了查看原始字符串的方式
2. 如果原始字符串被修改或销毁，`std::string_view` 可能会变得无效。因此需要确保 `std::string_view` 的生命周期不会超过它所查看的字符串
>It is the programmer's responsibility to ensure that `std::string_view` does not outlive the pointed-to character array

# Checkpoint 1
