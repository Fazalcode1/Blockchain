#include <bits/stdc++.h>
#include <openssl/sha.h>

struct Block {
    int index;
    std::string previousHash;
    std::time_t timestamp;
    std::string data;
    std::string hash;
    Block(int idx, const std::string& prevHash, const std::string& blockData)
        : index(idx), previousHash(prevHash), timestamp(std::time(nullptr)), data(blockData) {
        hash = calculateHash();
    }
    std::string calculateHash() const {
        std::stringstream ss;
        ss << index << previousHash << timestamp << data;

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((const unsigned char*)ss.str().c_str(), ss.str().length(), hash);

        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }

        return hashStream.str();
    }
};

class Blockchain {
public:
    Blockchain() {
        chain.emplace_back(createGenesisBlock());
    }
    Block createGenesisBlock() const {
        return Block(0, "0", "Genesis Block");
    }
    Block getLatestBlock() const {
        return chain.back();
    }
    void addBlock(const std::string& blockData) {
        const Block& previousBlock = getLatestBlock();
        int newIndex = previousBlock.index + 1;
        std::string newHash = calculateHash(newIndex, previousBlock.hash, blockData);
        chain.emplace_back(Block(newIndex, previousBlock.hash, blockData));
    }
std::vector<Block> chain;
private:
    std::string calculateHash(int index, const std::string& previousHash, const std::string& data) const {
        std::stringstream ss;
        ss << index << previousHash << data;

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((const unsigned char*)ss.str().c_str(), ss.str().length(), hash);

        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }

        return hashStream.str();
    }
};

int main() {
    Blockchain blockchain;
    blockchain.addBlock("Data 1");
    blockchain.addBlock("Data 2");
    blockchain.addBlock("Data 3");

    for (const Block& block : blockchain.chain) {
        std::cout << "Block Index: " << block.index << std::endl;
        std::cout << "Previous Hash: " << block.previousHash << std::endl;
        std::cout << "Timestamp: " << std::asctime(std::localtime(&block.timestamp));
        std::cout << "Data: " << block.data << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
