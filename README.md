PG Prototype1
===

# 必要要件

* Unreal Ungine 5.1
* VSCode
* .NET Framework 4.6.2 Target Pack
* .NET Framework 4.6.2.SDK
* MSVC v142 VS 2019 C++ x64/x86 ビルドツール (v14.29-16.10)
* Windows 10 SDK (10.0.18362.0)

# インストール

## 1. リポジトリーをダウンロード

```
$ git clone git@github.com:rog-works/PG_Prot1.git
```

## 2. プロジェクト用のファイルを自動生成

`PG_P1.uproject`を右クリックし「Generate Visual Studio project files」をクリック

## 3. IntelliSence用の設定ファイルを修正

`c_cpp_properties.json.example`の以下エントリーを、`c_cpp_properties.json`をコピー＆ペースト

* `compilerCommands`
* `includePath`
* `defines`

## 4. 実行

VSCodeで実行とデバッグから実行環境を選択して開始
