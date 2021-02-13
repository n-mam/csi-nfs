@echo off
SETLOCAL

SET NAMESPACE=xxx

minikube kubectl -- delete namespace %NAMESPACE%

minikube kubectl -- apply -f common.yaml

minikube kubectl -- apply -f controller.yaml

minikube kubectl -- get deploy -n %NAMESPACE%

minikube kubectl -- rollout status deploy/xxx-controller-deployment -n %NAMESPACE%

minikube kubectl -- describe deploy/xxx-controller-deployment -n %NAMESPACE%

minikube kubectl -- get rs -n %NAMESPACE%

minikube kubectl -- get pods -n %NAMESPACE%

minikube kubectl -- get pods POD_NAME_HERE -o jsonpath='{.spec.containers[*].name}' -n %NAMESPACE%

ENDLOCAL
