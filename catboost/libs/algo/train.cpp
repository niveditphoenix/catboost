#include "train.h"

class TLoglossError;
class TCrossEntropyError;
class TRMSEError;
class TQuantileError;
class TLogLinQuantileError;
class TMAPError;
class TPoissonError;
class TMultiClassError;
class TMultiClassOneVsAllError;
class TPairLogitError;
class TQueryRmseError;
class TCustomError;
class TUserDefinedPerObjectError;
class TUserDefinedQuerywiseError;

TErrorTracker BuildErrorTracker(bool isMaxOptimal, bool hasTest, TLearnContext* ctx) {
    const auto& odOptions = ctx->Params.BoostingOptions->OverfittingDetector;
    return TErrorTracker(odOptions->OverfittingDetectorType,
                         isMaxOptimal,
                         odOptions->AutoStopPValue,
                         odOptions->IterationsWait,
                         true,
                         hasTest);
}

template <typename TError>
void TrainOneIter(const TTrainData& data,  TLearnContext* ctx);

TTrainOneIterationFunc GetOneIterationFunc(ELossFunction lossFunction) {
    switch (lossFunction) {
        case ELossFunction::Logloss:
            return TrainOneIter<TLoglossError>;
            break;
        case ELossFunction::CrossEntropy:
            return TrainOneIter<TCrossEntropyError>;
            break;
        case ELossFunction::RMSE:
            return TrainOneIter<TRMSEError>;
            break;
        case ELossFunction::MAE:
        case ELossFunction::Quantile:
            return TrainOneIter<TQuantileError>;
            break;
        case ELossFunction::LogLinQuantile:
            return TrainOneIter<TLogLinQuantileError>;
            break;
        case ELossFunction::MAPE:
            return TrainOneIter<TMAPError>;
            break;
        case ELossFunction::Poisson:
            return TrainOneIter<TPoissonError>;
            break;
        case ELossFunction::MultiClass:
            return TrainOneIter<TMultiClassError>;
            break;
        case ELossFunction::MultiClassOneVsAll:
            return TrainOneIter<TMultiClassOneVsAllError>;
            break;
        case ELossFunction::PairLogit:
            return TrainOneIter<TPairLogitError>;
            break;
        case ELossFunction::QueryRMSE:
            return TrainOneIter<TQueryRmseError>;
            break;
        case ELossFunction::Custom:
            return TrainOneIter<TCustomError>;
            break;
        case ELossFunction::UserPerObjErr:
            return TrainOneIter<TUserDefinedPerObjectError>;
            break;
        case ELossFunction::UserQuerywiseErr:
            return TrainOneIter<TUserDefinedQuerywiseError>;
            break;
        default:
            CB_ENSURE(false, "provided error function is not supported");
    }
}
