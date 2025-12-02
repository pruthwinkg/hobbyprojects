FROM python:3.9-alpine

# Install bash
RUN apk add --no-cache bash procps

# Copy requirements files from the build context (./virtual_dataplane/web_app)
COPY web_app/requirements.txt /code/requirements-service.txt
COPY common/requirements.txt /code/common-requirements.txt

# Install Python dependencies
RUN pip install -r /code/requirements-service.txt
RUN pip install -r /code/common-requirements.txt

# Set the working directory to /code/light
WORKDIR /code

EXPOSE 7000
CMD ["python", "-m", "web_app.wsgi"]
