#include "CommandList.h"

CommandList::CommandList () {
    this->curr_idx_ = -1;
    this->prev_idx_ = this->curr_idx_ - 1;
    this->next_idx_ = this->curr_idx_ + 1;
}

bool CommandList::isEmpty () {
    return this->curr_idx_ < 0;
}

void CommandList::append (Command * command) {
    this->cmdList_.emplace_back(command);
    this->moveCurrentIdx_();
}

Command * CommandList::previous () {
    return this->prev_idx_ < 0 ?
        nullptr : cmdList_.at(this->prev_idx_);
}

Command * CommandList::next () {
    return this->next_idx_ >= this->cmdList_.size() ?
        nullptr : cmdList_.at(this->next_idx_);
}

Command * CommandList::current () {
    return this->curr_idx_ < 0 ?
        nullptr : this->cmdList_.at(this->curr_idx_);
}

void CommandList::moveCurrentIdx_ () {
    this->prev_idx_ = this->curr_idx_;
    this->curr_idx_ += 1;
    this->next_idx_ = this->curr_idx_ + 1;
}

CommandList::~CommandList() {

}