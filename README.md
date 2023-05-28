# Bs Drogon

## ws

url

```shell
ws://localhost:8090/bsws
```

join room `dev_tag`

```shell
ws://localhost:8090/bsws?dev_tag=rn
```

websocket test website

[wstool](https://wstool.js.org/)

[websocket online](https://www.hake.cc/tools/websocket/)

## redis

### Post

```
curl --location --request POST 'localhost:8090/redisclient/key1' \
--header 'Content-Type: application/json' \
--data-raw '{
  "value": "{\"k1\":1}"
}'
```

### Get

```
curl --location --request GET 'localhost:8090/redisclient/key1'
```

### api

index

```shell
localhost:8090
```

## logs

logs: 'projectDir/logs'

html: 'projectDir/index.html'

config: 'projectDir/config.json'

## build

```shell
mkdir build 

cd build

cmake ..

make
```

## libs

**Drogon**
[github](https://github.com/drogonframework/drogon)
[docs-cn](https://www.bookstack.cn/read/drogon-zh/CHN-03-%E5%BF%AB%E9%80%9F%E5%BC%80%E5%A7%8B.md)

**Hiredis**
[github](https://github.com/redis/hiredis)
