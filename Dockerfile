FROM public.ecr.aws/lambda/provided:al2
COPY bin/ bin/
COPY lib/ lib/
COPY bootstrap bootstrap
ENTRYPOINT [ "./bootstrap" ]  
