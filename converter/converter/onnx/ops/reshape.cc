#include "core/op_converter.h"
#include "onnx/onnx_utils.h"
#include "onnx.pb.h"

DECLARE_OP_CONVERTER(Reshape);

void ReshapeOpConverter::SetTensorInfo(dlxnet::TensorProto* dlcl_tensor,
        int tensor_index){
    LOG(FATAL)<<"Cannot set tensor info for reshape due to the only one input tensor";
}

void  ReshapeOpConverter::Run(dlxnet::NodeProto* dst_node, const void* src_node){
    dlxnet::ReshapeAttribute* dst_attr = dst_node->mutable_attr()->mutable_reshape_attr();
    const auto src_node_onnx = reinterpret_cast<const onnx::NodeProto*>(src_node);
    std::string res;
    for(int i=0;i<src_node_onnx->attribute_size();i++){
        const onnx::AttributeProto& attr = src_node_onnx->attribute(i);
        if(attr.name()=="-1"){
            // dst_attr->set_axis(attr.i());
        }else{
            ParseAttrValueToString(attr, &res);
            LOG(INFO)<<res;
        }
    }
}


REGISTER_OP_WITH_NAME(ReshapeOpConverter, "Reshape");
