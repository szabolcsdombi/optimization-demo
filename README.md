# optimization-demo

```
python -m pytest test.py \
    --benchmark-disable-gc \
    --benchmark-warmup=on \
    --benchmark-min-time=1.0 \
    --benchmark-min-rounds=10 \
    --benchmark-columns=mean,stddev,median,ops \
    --benchmark-sort=mean
```
