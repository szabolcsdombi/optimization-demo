FROM python:3.11.3
RUN pip install -U pip wheel setuptools && pip install pytest==7.4.0 pytest-benchmark[histogram]==4.0.0

COPY mymodule /mymodule
RUN pip install /mymodule

COPY test.py /test.py

CMD python -W ignore -m pytest test.py \
    --benchmark-disable-gc \
    --benchmark-warmup=on \
    --benchmark-min-time=1.0 \
    --benchmark-min-rounds=10 \
    --benchmark-columns=mean,stddev,median,ops \
    --benchmark-sort=mean \
    --benchmark-histogram=/out/histogram
