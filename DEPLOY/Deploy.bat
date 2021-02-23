@echo off
SETLOCAL

REM kubectl delete namespace xxx

kubectl apply -f rbac.yaml
kubectl apply -f controller.yaml
kubectl apply -f node.yaml
kubectl get pods -n xxx

REM During the nfs-server.yaml deployment, a new service nfs-server will 
REM be created which exposes the NFS server endpoint nfs-server.default.svc.cluster.local 
REM and the share path /. You can specify PersistentVolume or StorageClass using these information.

REM kubectl get deploy -n xxx
REM kubectl rollout status deploy/xxx-controller-deployment -n xxx
REM kubectl describe deploy/xxx-controller-deployment -n xxx
REM kubectl get rs -n xxx
REM --- list all containers of a pod
REM kubectl get pods [POD] -o jsonpath='{.spec.containers[*].name}' -n xxx
REM --- pod's container logs
REM kubectl logs [POD] -c csi-msys-driver -n xxx
REM minikube ssh
REM delete msys-driver-image:latest using docker rmi <tag>

eval $(minikube docker-env)
docker build -t msys-driver-image .

REM minikube ssh
REM docker images my-image
REM kubectl exec [pod] -c [con] -n xxx -it -- /bin/sh

ENDLOCAL

kubectl get pv
kubectl get pvc
kubectl get pods

kubectl patch pv pv-nfs -p '{"metadata":{"finalizers":null}}'
kubectl patch pvc pvc-nfs-static -p '{"metadata":{"finalizers":null}}'

kubectl delete namespace xxx
kubectl delete sc nfs-sc
kubectl delete pod my-pod
kubectl delete pvc pvc-nfs-static
kubectl delete pv pv-nfs
kubectl delete pvc pvc-nfs-dynamic


REM setup nfs server on the minikube vm and export
REM the root share off /home/nmam/nfs_root/

mount -o nolock 192.168.43.162:/home/nmam/nfs_root/ /mnt/nfs_mount
umount -f -l /mnt/nfs_mount/