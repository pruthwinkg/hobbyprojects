FROM python:3.9-alpine
RUN apk add --no-cache bash
COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt
WORKDIR /code
#EXPOSE 9003 (Do not expose this. All APIs here are internal)
CMD ["python", "-m", "authentication.wsgi"]