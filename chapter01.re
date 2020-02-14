= JavaScriptで出来ること

まずはじめに、一番大事なJavaScriptで出来ることついて整理してみたいと思います。

== Geolocation API

ガラケー時代に位置情報サービスを作られたことがある方はキャリア毎に異なる実装が必要になり辛い思いをしたことかもしれませんが、流石に今はそんなことをする必要はなくなっています。W3C@<fn>{W3C}が位置情報を取得するための「Geolocation API」@<fn>{GeoAPI}というAPIを定義しており、このAPIを使うことで、同一のコードで異なるOS・ブラウザで位置情報を取得出来るようになっています。
//footnote[W3C][「World Wide Web Consortium」の略称で、Web技術の標準化を行う非営利団体の名称。]
//footnote[GeoAPI][https://w3c.github.io/geolocation-api/]

=== メソッド

Geolocation APIでは、下記3つのメソッドが定義されています。

 : Geolocation.getCurrentPosition()
    デバイスの現在位置を取得するメソッド。

 : Geolocation.watchPosition()
    デバイスの位置が変化する度に呼び出されるコールバック関数を登録するメソッド。

 : Geolocation.clearWatch()
    watchPosition()で登録した関数を解除するメソッド。

上記APIを使用することで、現在位置の取得や、現在位置が変更になった際に何か処理を行う、ということが出来るようになっています。APIの具体的な使い方については次章で説明します。

=== 精度

位置情報の精度は、GPSによる取得なのか、Wi-Fiアクセスポイントなのか、はたまたIPアドレスなのかによって異なります。

Geolocation APIでは、位置情報を取得する際に何の値を使用するかを明確に指定する事は出来ません。代わりに、APIに@<code>{enableHighAccuracy}というオプションを使用することで、より正確な値を取得するよう指定することが出来るようになっています。デフォルトは無効になっているので、精度の高い情報が必要な場合、このオプションを指定する必要があります@<fn>{enableHighAccuracy}。
//footnote[enableHighAccuracy][精度が高い情報を取得出来るようになるかわりに、測位結果の取得に時間がかかったり、消費電力が高まる可能性があります。]

=== サポート状況

Geolocation APIは比較的古くからあるAPIであり、例えばGoogle Chromeではバージョン4から、Safariではバージョン5からサポートしています。おそらく通常利用されるブラウザでは問題ないかと思います。もし特殊なブラウザをサポートする必要がある場合、Can I use@<fn>{caniuse}でサポート状況を確認してください。
//footnote[caniuse][https://caniuse.com/#feat=geolocation]

なお、Geolocation APIはHTTPS環境でしか動作しない、という制限があります。注意してください。

=== PCでの使用

スマートフォンであれば、前節で説明したGeolocation APIを使用して期待通りに位置情報を取得出来ると思います。ではPCではどうしょうか。GPSレシーバをつけたPCで、位置情報を正確に取得出来るか、というと、残念ながら執筆時点では難しいようです。

たとえばWindowsの場合、GPSレシーバでから位置情報を取得する倍、OSが提供しているWindows.Devices.Geolocation@<fn>{windows}というAPIを使う必要があるのですが、Geolocation APIでこのAPIを使用しているかどうかはブラウザ依存です。
//footnote[windows][https://docs.microsoft.com/en-us/uwp/api/Windows.Devices.Geolocation]

たとえばChromeの場合、まだこのAPIを使用しての実装はされていません。そのため、GPS機器がある場合でも、GPS精度の位置情報は取得出来ません@<fn>{chrome_issue}ので注意してください。
//footnote[chrome_issue][Chromeのバグトラッキングシステムに要望は登録されているので、いずれ実装される可能性はあります。https://bugs.chromium.org/p/chromium/issues/detail?id=968883]

=== 問題点

Geolocation APIにより位置情報の取得はできそうです。しかしこのAPIはフォアグラウンドでの使用しか想定されていません。そのため、バックグラウンド@<fn>{serviceworker}で動作して位置情報を取得し続けることや、特定のエリアに入った時に何かアクションをする@<fn>{fencing}、ということが出来ません。
//footnote[serviceworker][要はService WorkersでGeolocation APIを使用することが出来ません。]
//footnote[fencing]["ジオフェンス"と呼ばれる仕組みです。https://en.wikipedia.org/wiki/Geo-fence]

他にも、例えばAPIのインターフェイスに関する問題があります。Geolocation APIは比較的昔に仕様が策定されたという事もあり、類似の他のAPIとGeolocation APIとインターフェイスが異なってしまってしまっています。

当然、これらの問題はそのまま、というわけではなく、問題を解決するための対応が行われています。次節ではその対応について見ていきます。

== Geolocation Sensor

前節で説明したGeolocation APIの問題を解決し、更にセキュリティやプライバシーについても配慮した新しいAPIである、「Geolocation Sensor API」@<fn>{gs}の策定が行われています。
//footnote[gs][https://w3c.github.io/geolocation-sensor]

"行われています"と記載したとおり、現在進行中で対応が進んでいる状態です。残念ながらまだ草案であり、ブラウザでも当然実装はされていません。そのため、Geolocation APIであげた問題点については、現在対応するすべはありません。

=== Geolocation Sensorの今後

Geolocation Sensorは「Devices and Sensors Working Group」@<fn>{das}というワーキンググループで管理されています。名前の通りデバイスとセンサーに関するAPIを策定するワーキンググループで、加速度を取得するAPIや、バッテリーの状態を取得するAPIの作成を行っています。

その「Devices and Sensors Working Group」のロードマップ@<fn>{roadmap}によると、2020のQ2にCandidate Recommendation(勧告候補)になる予定のようです。勧告候補になると諮問委員会への実装依頼が行われる為、もしかしたら2020年中には試せるような状態になるかもしれません。
//footnote[das][https://www.w3.org/das/]
//footnote[roadmap][https://www.w3.org/das/roadmap]

== まとめ

現状をまとめると、

 * フォアグラウンドでの位置情報の取得は出来る
 * バックグラウンドの取得は(まだ)出来ない
 * ジオフェンス用のAPIは(まだ)ない

という状態です。ちなみに筆者はバックグラウンドでの処理を行いたかったのでしたが駄目でした。残念。

ちなみに、"JavaScript"で"ジオフェンス"について調査すると、Geofencing API@<fn>{fencing}というAPIについて情報にヒットすることがあります。これは正式に廃止された仕様であり、使用出来ることはありませんので注意してください。
//footnote[fencing][https://w3c.github.io/geofencing-api/]
