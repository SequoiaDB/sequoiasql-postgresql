SequoiaDB Foreign Data Wrapper for PostgreSQL
=============================================
SequoiaDB Foreign Data Wrapper(sdb_fdw) is a PostgreSQL extension to access to SequoiaDB easily and efficiently.


Building
--------
This version of sdb_fdw only works with PostgreSQL Version 9.3.4. Please ensure that it's installed in your computer. If it has, you can skip step 1-2.
1. Download [postgresql-9.3.4.tar.gz](https://www.postgresql.org/ftp/source/v9.3.4/) and extract it.

2. Make and install postgresql
    ```
    # ./configure
    # make && make install
    ```
   If you want to choose different path than /usr/local/pgsql, you can specify prefix to specify pgsql934
eg: ./configure --prefix=/usr/local/pgsql934
3. Export PostgreSQL installation's `bin` directory to PATH. For example:
    ```
    # export PATH=/usr/local/pgsql934:$PATH
    ```
4. Copy SequoiaDB C driver to this folder in a new folder named 'sdbdriver'. You can find the driver in SequoiaDB installation directory, or just download the driver package from SequoiaDB<http://download.sequoiadb.com/cn/> official website. For example:
    ```
    # DRIVER_PATH=/opt/sequoiadb
    # mkdir sdbdriver
    # cp -r ${DRIVER_PATH}/include sdbdriver/
    # cp -r ${DRIVER_PATH}/lib sdbdriver/
    ```
5. Build the plugin.
    ```
    # make all
    ```


License
-------
License under the Apache License, Version 2.0. See LICENSE for more information. Copyright(c) 2011-2018, SequoiaDB and/or its affiliates. All rights reserved.
