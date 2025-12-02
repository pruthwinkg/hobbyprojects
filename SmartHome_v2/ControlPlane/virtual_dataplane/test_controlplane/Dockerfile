FROM python:3.9-alpine
RUN apk add --no-cache bash
COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt
WORKDIR /code
EXPOSE 40000
CMD ["python", "-m", "test_controlplane.controlplane"]