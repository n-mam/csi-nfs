@echo off
SETLOCAL

REM kubectl delete namespace xxx

REM kubectl apply -f common.yaml

REM kubectl apply -f controller.yaml

REM kubectl get deploy -n xxx

REM kubectl rollout status deploy/xxx-controller-deployment -n xxx

REM kubectl describe deploy/xxx-controller-deployment -n xxx

REM kubectl get rs -n xxx

REM kubectl get pods -n xxx

REM --- list all containers of a pod

REM kubectl get pods POD_NAME_HERE -o jsonpath='{.spec.containers[*].name}' -n xxx

REM --- pod's container logs

REM kubectl logs POD_NAME_HERE -c csi-msys-driver -n xxx

REM minikube ssh
REM delete msys-driver-image:latest using docker rmi <tag>

REM eval $(minikube docker-env)
REM docker build -t msys-driver-image .
REM minikube ssh
REM docker images my-image

REM  docker run -i debian:buster-slim /bin/sh

ENDLOCAL
