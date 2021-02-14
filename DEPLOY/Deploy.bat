@echo off
SETLOCAL

SET NAMESPACE=xxx

kubectl delete namespace xxx

kubectl apply -f common.yaml

kubectl apply -f controller.yaml

kubectl get deploy -n xxx

kubectl rollout status deploy/xxx-controller-deployment -n xxx

kubectl describe deploy/xxx-controller-deployment -n xxx

kubectl get rs -n xxx

kubectl get pods -n xxx

REM list all pod containers

kubectl get pods POD_NAME_HERE -o jsonpath='{.spec.containers[*].name}' -n xxx

REM pod's container logs

kubectl logs POD_NAME_HERE -c POD_CONTAINER_NAME_HERE -n xxx

REM mount /home/nmam/csi-nfs/ repo into minikube's vm 

minikube mount /home/nmam/csi-nfs/:/home/docker/csi-nfs

REM eval $(minikube docker-env)
REM docker build -t my-image .
REM minikube ssh
REM docker images my-image

ENDLOCAL
