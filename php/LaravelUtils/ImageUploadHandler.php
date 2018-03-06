<?php
/**
 * 处理图片上传，依赖intervention/image进行图片裁剪
 */

namespace App\Handlers;

use Intervention\Image\Facades\Image;

class ImageUploadHandler
{
    protected $allowedExt = ['png', 'jpg', 'gif', 'jpeg'];

    public function save($file, $folder, $filePrefix, $maxWidth = false)
    {
        $folderName = "uploads/images/$folder/" . date('Ym') . '/' . date('d') . '/';

        $uploadPath = public_path() . '/' . $folderName;

        $extension = strtolower($file->getClientOriginalExtension()) ?: 'png';

        $filename = $filePrefix . '_' . time() . '_' . str_random(10) . '.' . $extension;

        if (!in_array($extension, $this->allowedExt)) {
            return false;
        }

        $file->move($uploadPath, $filename);

        if ($maxWidth && $extension != 'gif') {
            $this->reduceSize($uploadPath . '/' . $filename, $maxWidth);
        }

        return [
            'path' => config('app.url') . "/$folderName$filename",
        ];
    }

    public function reduceSize($filePath, $maxWidth)
    {
        $image = Image::make($filePath);
        $image->resize(
            $maxWidth,
            null,
            function($constraint) {
                $constraint->aspectRatio();
                $constraint->upsize();
            }
        );

        $image->save();
    }
}
