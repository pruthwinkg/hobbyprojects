FROM python:3.9-alpine

# Install bash and Supervisor
RUN apk add --no-cache bash supervisor procps

# Copy requirements files from the build context (./virtual_dataplane/light)
COPY light/requirements.txt /code/requirements-service.txt
COPY common/requirements.txt /code/common-requirements.txt

# Install Python dependencies
RUN pip install -r /code/requirements-service.txt
RUN pip install -r /code/common-requirements.txt

# Create log directory
RUN mkdir -p /var/log/supervisor

# Copy supervisord configuration file
COPY light/supervisord.conf /etc/supervisor/conf.d/supervisord.conf
COPY light/supervisord.conf /etc/supervisord.conf

# Set the working directory to /code/light
WORKDIR /code

# Start supervisord
CMD ["/usr/bin/supervisord", "-c", "/etc/supervisord.conf"]
