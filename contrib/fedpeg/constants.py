#!/usr/bin/env python2

import os

class FedpegConstants:
	# VARIOUS SETTINGS...
	user = os.environ["RPC_USER"]
	password = os.environ["RPC_PASS"]
	sidechain_url = "http://" + user + ":" + password + "@127.0.0.1:4251"
	bitcoin_url = "http://" + user + ":" + password + "@127.0.0.1:18332"

	redeem_script = "522102174eda07d3dc89145f4b217702250d76d753229f11b380ecbb1f7c5c5c342ae02102519b8fb02f3c44f9912eda3da8651a7d63a8232479fbe880ded1b092aa14da632102a01aaa27b468ec3fb2ae0c2a9fa1d5dce9b79b35062178f479156d8daa6c0e5053ae"
	redeem_script_address = "2N7QCgeVbfAMk1XmhyYZ1ponRbjvN1U7ZXz"
	secondScriptPubKeyHash = "9eac001049d5c38ece8996485418421f4a01e2d7"
	secondScriptPubKey = "OP_DROP 144 OP_LESSTHANOREQUAL"


	blocksigning_private_key = "cW1vgxD5NruwGBrgnK1tBUqPPWFzgk3TkfJzcTU4QooVrF2xRYoX"
	functionary_private_key = "cSccnjhCFsGr74bg2toEX2odHmnsdR3TGRFX8BNYb6U74jymAfer"

	bitcoin_tx_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../bitcoin-tx")
	contracthashtool_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../../../contracthashtool/contracthashtool")
	is_testnet = 1

	#Bitcoin:
	bitcoin_genesis_hash = "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
	#Testnet:
	#bitcoin_genesis_hash = "000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"

	nodes =["192.168.1.115", "173.31.39.168"]
	my_node = "192.168.1.115"

	# Set this to non-None if you're using a proxy (eg for Tor)
	# Note that this requires ZMQ 4.1
	socks_proxy = None
	#socks_proxy = "127.0.0.1:9050"

	def __init__(self):
		# Derived constants (dont touch)
		self.testnet_arg = ""
		if self.is_testnet == 1:
			self.cht_testnet_arg = "-t"
			self.btc_testnet_arg = "-testnet"
		else:
			self.cht_testnet_arg = ""
			self.btc_testnet_arg = ""

		self.sigs_required = int(self.redeem_script[:2], 16) - 0x50

		self.inverse_bitcoin_genesis_hash = "".join(reversed([self.bitcoin_genesis_hash[i:i+2] for i in range(0, len(self.bitcoin_genesis_hash), 2)]))
