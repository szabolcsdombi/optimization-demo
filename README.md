# optimization-demo

## Results

```
------------------------------------------ benchmark: 3 tests ------------------------------------------
Name (time in ns)             Mean            StdDev                Median            OPS (Kops/s)
--------------------------------------------------------------------------------------------------------
test_magic_code          83.1061 (1.0)      0.7204 (22.09)       82.8925 (1.0)       12,032.8104 (1.0)
test_optimized_code     338.3712 (4.07)     0.0326 (1.0)        338.3669 (4.08)       2,955.3341 (0.25)
test_python_code      1,288.4041 (15.50)    0.6493 (19.91)    1,288.4681 (15.54)        776.1540 (0.06)
--------------------------------------------------------------------------------------------------------
```

This result was generated with github actions [here](https://github.com/szabolcsdombi/optimization-demo/actions/runs/5421123701/jobs/9856158226) with the following command:

```console
python -m pytest test.py \
    --benchmark-disable-gc \
    --benchmark-warmup=on \
    --benchmark-min-time=1.0 \
    --benchmark-min-rounds=10 \
    --benchmark-columns=mean,stddev,median,ops \
    --benchmark-sort=mean
```
