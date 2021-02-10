# csi-nfs
csi nfs driver

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