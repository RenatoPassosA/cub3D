FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    libcriterion-dev \
    libxext-dev \
    libx11-dev \
    libbsd-dev \
    git \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

CMD ["make", "test"]
