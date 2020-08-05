This is a wrapper to run CAIN.
You can specify start event number and end event number and
will get LCIO or ROOT output file.
The script in run directory is supposed to be used at KEKCC. 

## How to compile:

```
(edit setup.sh according to your environment)
source setup.sh
make
```

## How to run:
```
(source setup.sh // if you haven't set yet)
cd run

(edit conf.py to specify scan parameters and start/end event)
python makeRunConfigurations.py  (This creates output directories and configuration files)
python manyRun.py (This submits jobs according to the configuration newly created above)
```
