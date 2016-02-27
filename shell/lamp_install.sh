#!/bin/bash

TEMP_DIR='/tmp/install_temp/'

echo "Welcome to this script."
echo "now, you need sereval steps to confirm what you want to install."

read -p "step 1: choose web server you want to install(nginx/apache), default is nginx: " WEB_SERVER
read -p "step 2: choose version of php which you want to install(default is 5.6.18): " PHP_VERSION
read -p "step 3: choose version of mysql which you want to install(default is 5.7): " MYSQL_VERSION
read -p "step 4: choose the directory where software will install(default is /usr/local): " INSTALL_DIR

#处理默认值
WEB_SERVER=${WEB_SERVER:-nginx}
PHP_VERSION=${PHP_VERSION:-5.6.18}
MYSQL_VERSION=${MYSQL_VERSION:-5.7}

#处理安装目录，如果目录不存在，提醒用户再次确认，防止输入错误
if [ ! -z $INSTALL_DIR ]; then
	while [ ! -d $INSTALL_DIR ]
	do
		read -p "The directory($INSTALL_DIR) you choose is not exist, do you want to create it(y/n): " tmp
		if [ $tmp = 'y' ]; then
			mkdir -p $INSTALL_DIR
			break
		else
			read -p "step 4: choose the directory where software will install(default is /usr/local): " INSTALL_DIR
		fi
	done
	#为目录后面加上斜线
	INSTALL_DIR=${INSTALL_DIR%/}
	INSTALL_DIR=${INSTALL_DIR}/
fi

#安装必要的依赖库
yum group -y install development
yum install -y libxml2-devel openssl-devel libcurl-devel libjepg-devel libpng-devel libicu-devel openldap-devel

curPath=`pwd`
mkdir -p $TEMP_DIR
cd $TEMP_DIR

#安装libpng
wget ftp://ftp.simplesystems.org/pub/libpng/png/src/libpng16/libpng-1.6.21.tar.gz

#安装zlib
wget "http://zlib.net/zlib-1.2.8.tar.gz"

#安装libjpeg
wget "http://www.ijg.org/files/jpegsrc.v9.tar.gz"

#安装freetype
wget "http://download.savannah.gnu.org/releases/freetype/freetype-2.6.tar.gz"

#安装gd
wget "https://github.com/libgd/libgd/releases/download/gd-2.1.1/libgd-2.1.1.tar.gz"

#安装openssl
wget "ftp://ftp.openssl.org/source/openssl-1.0.2f.tar.gz"
