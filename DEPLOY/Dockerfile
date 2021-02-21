# docker build 
FROM centos:latest
WORKDIR /app
ADD "server" /app
RUN yum -y install nfs-utils epel-release jq && yum clean all
ENTRYPOINT ["/app/server"]
 