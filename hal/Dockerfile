FROM matheuscastello/binutils

# This docker run only to build the project so use this:
# docker run -it -v $(pwd):/project --rm matheuscastello/build $@

# install build deps
#RUN apt-get -y update && apt-get install -y \
#	
#	&& apt-get clean && apt-get autoremove && rm -rf /var/lib/apt/lists/*

# get project REMEMBER to mount the volume from your project to /project
WORKDIR /project

# build script
COPY buildscript.sh .
ENTRYPOINT [ "/project/buildscript.sh" ]
