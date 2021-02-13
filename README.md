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

```sh
go get github.com/kubernetes-csi/csi-test/cmd/csi-sanity
"C:\Users\nmam\go\bin\csi-sanity.exe" --csi.endpoint dns://127.0.0.1:50051
"C:\Users\nmam\go\bin\csi-sanity.exe" --csi.endpoint 127.0.0.1:50051 ----- use this for testing
```
### Deployment

```sh
minikube kubectl -- apply -f common.yaml
namespace/csi-msys-ns created
serviceaccount/csi-msys-sa created
```

```sh
minikube kubectl -- apply -f controller.yaml
deployment.apps/csi-msys-controller created
```

```sh
minikube kubectl -- get deployments --all-namespaces
NAMESPACE              NAME                        READY   UP-TO-DATE   AVAILABLE   AGE
csi-msys-ns            csi-msys-controller         1/1     1            1           18s
kube-system            coredns                     1/1     1            1           7d19h
kubernetes-dashboard   dashboard-metrics-scraper   1/1     1            1           7d19h
kubernetes-dashboard   kubernetes-dashboard        1/1     1            1           7d19h
```

if not ready like this...

```sh
NAMESPACE              NAME                        READY   UP-TO-DATE   AVAILABLE   AGE
csi-msys               csi-msys-controller         0/1     0            0           13m
kube-system            coredns                     1/1     1            1           7d16h
kubernetes-dashboard   dashboard-metrics-scraper   1/1     1            1           7d15h
kubernetes-dashboard   kubernetes-dashboard        1/1     1            1           7d15h
```

then proceed with :

```sh
minikube kubectl -- rollout status deployment/csi-msys-controller -n csi-msys-ns
deployment "csi-msys-controller" successfully rolled out
```

```sh
minikube kubectl -- describe deploy/csi-msys-controller -n csi-msys-ns
:
Conditions:
  Type           Status  Reason
  ----           ------  ------
  Available      True    MinimumReplicasAvailable
  Progressing    True    NewReplicaSetAvailable
OldReplicaSets:  <none>
NewReplicaSet:   csi-msys-controller-6476845895 (1/1 replicas created)
Events:
  Type    Reason             Age   From                   Message
  ----    ------             ----  ----                   -------
  Normal  ScalingReplicaSet  99s   deployment-controller  Scaled up replica set csi-msys-controller-6476845895 to 1
```

```sh
minikube kubectl -- get replicasets -n csi-msys-ns
NAME                             DESIRED   CURRENT   READY   AGE
csi-msys-controller-6476845895   1         1         1       2m59s
```

```sh
minikube kubectl -- describe replicaset csi-msys-controller-6476845895 -n csi-msys-ns

Good:

Events:
  Type    Reason            Age    From                   Message
  ----    ------            ----   ----                   -------
  Normal  SuccessfulCreate  3m38s  replicaset-controller  Created pod: csi-msys-controller-6476845895-nfld4

Bad:

Events:
  Type     Reason        Age                 From                   Message
  ----     ------        ----                ----                   -------
  Warning  FailedCreate  59m (x19 over 81m)  replicaset-controller  Error creating: pods "csi-msys-controller-64696d7cc9-" is forbidden: error looking up service account csi-msys/csi-msys-controller-sa: servicea
ccount "csi-msys-controller-sa" not found
```