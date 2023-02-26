FROM public.ecr.aws/lambda/provided:al2 as build

COPY build/api.zip api.zip
RUN yum install unzip -y
RUN unzip api.zip -d /tmp

FROM public.ecr.aws/lambda/provided:al2

COPY --from=build /tmp ./

ENTRYPOINT [ "./bootstrap" ]  
