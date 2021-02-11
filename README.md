# csi-nfs
csi nfs driver

### install grpc
```sh
$ git clone https://github.com/microsoft/vcpkg
$ ./vcpkg/bootstrap-vcpkg.sh
$ ./vcpkg/vcpkg install grpc
```
```sh
Windows:
  set SET CMAKE_PREFIX_PATH=d:\vcpkg\installed\x64-windows
Linux:
  export CMAKE_PREFIX_PATH=~/vcpkg/installed/x64-linux/
```

### Build
```sh
cd c:\csi-nfs
md build
cd build
cmake ..
cmake --build . --config Release
```

### csi-sanity 
go get github.com/kubernetes-csi/csi-test/cmd/csi-sanity

"C:\Users\nmam\go\bin\csi-sanity.exe" --csi.endpoint dns://127.0.0.1:50051
"C:\Users\nmam\go\bin\csi-sanity.exe" --csi.endpoint 127.0.0.1:50051