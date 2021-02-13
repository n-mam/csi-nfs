@echo off
SETLOCAL

SET NAMESPACE=msys-ns

minikube kubectl -- delete namespace %NAMESPACE%

minikube kubectl -- apply -f common.yaml

minikube kubectl -- apply -f controller.yaml

minikube kubectl -- get deployments --all-namespaces

minikube kubectl -- rollout status deployment/csi-msys-controller -n %NAMESPACE%

minikube kubectl -- describe deploy/csi-msys-controller -n %NAMESPACE%

minikube kubectl -- get replicasets -n %NAMESPACE%

ENDLOCAL
