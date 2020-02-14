= チュートリアル

ここでは、1章で説明したAPIを実際に使用してみたいと思います。1章で説明したとおり、Geolocation Sensorはまだ使用出来ない為、ここではGeolocation APIを使用したサンプルのみ記載しています。

https://github.com/y-yagi/gps-with-js-example に本章で説明したコードがありますので、合わせてご参照ください。

== Geolocation.getCurrentPosition

まずは、@<code>{Geolocation.getCurrentPosition}という現在位置を取得するメソッドについて説明します。早速コードです。

//listnum[getCurrentPosition_v1][getCurrentPosition_v1]{
<!DOCTYPE html>
<html>
  <head>
    <script>
    function getLocation() {
      if (navigator.geolocation) {
        navigator.geolocation.getCurrentPosition(showPosition);
      } else {
        alert("Geolocation is not supported by this browser.");
      }
    }

    function showPosition(position) {
      const pos = document.getElementById("pos");
      pos.innerHTML = "Latitude: " + position.coords.latitude +
        "<br>Longitude: " + position.coords.longitude;
    }
    </script>
  </head>
  <body>
    <button onclick="getLocation()">現在位置を表示</button>
    <p id="pos"></p>
  </body>
</html>
//}

ボタンを押すと現在位置の緯度経度を表示するだけのコードです。コードを見るだけで何をしているかわかりそうですが、簡単に解説します。

ボタンを押下すると、@<tt>{getLocation}関数が実行されます。@<tt>{getLocation}関数ではまず、はじめに、@<tt>{navigator.geolocation}を使用してGeolocation APIが使用出来るかどうかを確認しています。

Geolocation APIが使用出来る事を確認したら、@<tt>{Geolocation.getCurrentPosition}を呼び出します。@<tt>{Geolocation.getCurrentPosition}には、位置情報を取得出来た場合に実行するコールバック関数を指定します。@<tt>{Geolocation.getCurrentPosition}には他にも引数を指定出来ますが、これは後ほど説明します。

無事位置情報が取得出来たら、@<tt>{Geolocation.getCurrentPosition}に指定した@<tt>{showPosition}関数が実行されます。コールバック関数には、@<tt>{GeolocationPosition}オブジェクトが渡されます。

@<tt>{GeolocationPosition}オブジェクトは、現在位置と位置情報が取得された時間を保持しており、@<tt>{coords}プロパティを使用して現在位置を取得して、その値を表示しています。なお、@<tt>{coords}はは@<tt>{GeolocationCoordinates}オブジェクトを返します。今回は緯度経度だけ使用していますが、他にも高度などの情報も取得することが出来ます。

以上です。簡単ですね。

=== オプションを指定

続けて、@<code>{Geolocation.getCurrentPosition}にオプションを指定する方法について説明します。とはいっても殆ど前節のコードと同じです。diffだけ記載します。

//listnum[getCurrentPosition_v2][getCurrentPosition_v2]{
     <script>
     function getLocation() {
       if (navigator.geolocation) {
-        navigator.geolocation.getCurrentPosition(showPosition);
+        navigator.geolocation.getCurrentPosition(showPosition,
           error, { enableHighAccuracy: true });
       } else {
         alert("Geolocation is not supported by this browser.");
       }

       const button = document.getElementById("try");
     }
+
+    function error(err) {
+      console.warn(`Error: (${err.code}): ${err.message}`);
+    }
//}

@<tt>{Geolocation.getCurrentPosition}呼び出し時の引数を追加しています。

第一引数には位置情報が取得出来た際に実行するコールバック関数を指定しましたが、第二引数には位置情報の取得に失敗した際に実行するコールバック関数を指定します。たとえば、位置情報を取得するにはユーザの許可が必要ですが、ユーザが位置情報の取得を許可しなかった場合このコールバック関数が実行されます。

位置情報の取得に失敗した場合、コールバック関数にはエラー情報を保持した@<tt>{GeolocationPositionError}オブジェクトが渡されます。@<tt>{GeolocationPositionError}からはエラーコード(@<tt>{code})とエラーメッセージ(@<tt>{message})が取得出来ます。

上記コードでは、位置情報の取得に失敗時に実行する@<tt>{error}関数でエラーコードとエラーメッセージをコンソールに出力するようにしています。エラーメッセージはエラーの詳細についての文字列が取得出来ますが、ロケールについては定義されいていないので注意してください。
//footnote[locale][ブラウザの言語設定が日本語でも、エラーメッセージが英語になっている可能性があります。]

最後に第三引数についてです。第三引数には、@<tt>{Geolocation.getCurrentPosition}の挙動を指定するためのオプションを指定出来ます。

オプションには@<tt>{PositionOptions}オブジェクトを指定します。@<tt>{PositionOptions}オブジェクトには以下の三つの値を指定出来ます。

 : enableHighAccuracy
    高精度の結果を取得するかどうかを指定。trueを指定した場合、高精度な位置情報を取得するようになる。デフォルトはfalse。

 : timeout
  　位置情報の取得にかかる時間の上限を指定。デフォルトは@<tt>{Infinity}で、位置情報が得られるまで待つ。

 : maximumAge
    キャッシュされた位置情報の有効期限を指定。0を指定するとキャッシュを使用しない。@<tt>Infinity を指定した場合、必ずキャッシュを使用する。デフォルトは0。

今回のサンプルコードでは@<tt>{enableHighAccuracy}を指定して、高精度の結果が取得するようにしています。これにより、例えばGPS機器が内蔵されているスマートフォンの場合、より正確な結果が取得されるようになっています。

これで@<code>{Geolocation.getCurrentPosition}についての説明は終わりです。ここで実装したサンプルは、https://y-yagi.github.io/gps-with-js-example/getCurrentPosition.html で実際にブラウザからお試し頂けます。

== Geolocation.watchPosition

続いて、@<tt>{Geolocation.watchPosition}についてです。@<tt>{Geolocation.watchPosition}に指定する引数は、@<code>{Geolocation.getCurrentPosition}は同じで、位置情報を取得出来た場合に実行するコールバック関数、位置情報の取得に失敗した際に実行するコールバック関数、挙動を指定するためのオプションです。オプションに指定出来る値も@<code>{Geolocation.getCurrentPosition}と同じです。

@<code>{Geolocation.getCurrentPosition}が一度だけ位置情報を取得するのに対して、@<tt>{Geolocation.watchPosition}は機器の位置が変化する度に実行されます。

この監視を解除するには、@<tt>{Geolocation.clearWatch}を使用する必要があります。@<code>{Geolocation.getCurrentPosition}は戻り値としてIDを返すようになって、そのIDを@<tt>{Geolocation.clearWatch}にすると処理が解除されます。

APIの説明も終わったところでサンプルです。

//listnum[watchPosition][watchPosition]{
<!DOCTYPE html>
<html>
  <head>
    <script>
    function start() {
      if (navigator.geolocation) {
        const id = navigator.geolocation.watchPosition(showPosition,
          error, { enableHighAccuracy: true });
        document.getElementById("start").disabled = true;
        document.getElementById("stop").dataset.watchId = id;
        document.getElementById("stop").disabled = false;
      } else {
        alert("Geolocation is not supported by this browser.");
      }
    }

    function showPosition(position) {
      const pos = document.getElementById("pos");
      pos.innerHTML = "Latitude: " + position.coords.latitude +
        "<br>Longitude: " + position.coords.longitude;
    }

    function error(err) {
      console.warn(`Error: (${err.code}): ${err.message}`);
    }

    function stop() {
      const id = document.getElementById("stop").dataset.watchId;
      navigator.geolocation.clearWatch(id)
      document.getElementById("stop").disabled = true;
      document.getElementById("start").disabled = false;
    }
    </script>
  </head>
  <body>
    <button onclick="start()" id="start">開始</button>
    <button onclick="stop()" id="stop" disabled>停止</button>
    <p id="pos"></p>
  </body>
</html>
//}

@<tt>{開始}ボタンを押下すると@<tt>{Geolocation.watchPosition}を呼び出して位置情報の取得を開始します。@<tt>{Geolocation.watchPosition}の戻り値を@<tt>{停止}ボタンのデータ属性に設定し、@<tt>{停止}ボタン押下時に@<tt>{Geolocation.clearWatch}に渡すようにしています。

これで位置情報が変わる度に表示される緯度経度の値が更新されるようになりました。とはいえ、PCで開発している場合、実際に位置情報を変えるのは難しいです。

そんなときの為に、Google Chromeでは、Chrome DevTools のセンサーエミュレーションで位置情報データのオーバーライドが出来るようになっています。

Chrome DevTools のメインメニュー -> [More Tools] -> [Sensors] の[Geolocation]で値を変更出来ます。

@<tt>{Geolocation.watchPosition}が実際に動作するかを確認したい場合にご利用ください。なお、設定方法の詳細は、https://developers.google.com/web/tools/chrome-devtools/device-mode/device-input-and-sensors をご参照ください。
