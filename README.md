# optimization-demo

## Results

```
-------------------------------------------- benchmark: 2 tests ------------------------------------------
Name (time in ns)            Mean            StdDev                Median           OPS (Kops/s)
----------------------------------------------------------------------------------------------------------
test_optimized_code      317.0102 (1.0)      0.0384 (1.0)        317.0121 (1.0)       3,154.4725 (1.0)
test_python_code       1,149.9825 (3.63)     0.8864 (23.10)    1,149.8373 (3.63)        869.5785 (0.28)
----------------------------------------------------------------------------------------------------------
```

This result was generated with github actions [here](https://github.com/szabolcsdombi/optimization-demo/actions/runs/5423258436/jobs/9860949567) with the following command:

```console
python -m pytest test.py \
    --benchmark-disable-gc \
    --benchmark-warmup=on \
    --benchmark-min-time=1.0 \
    --benchmark-min-rounds=10 \
    --benchmark-columns=mean,stddev,median,ops \
    --benchmark-sort=mean
```
